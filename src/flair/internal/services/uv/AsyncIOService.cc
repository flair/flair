#include "flair/internal/services/uv/AsyncIOService.h"

namespace flair {
namespace internal {
namespace services {
namespace uv {
   
   using flair::events::Event;
   
   AsyncIOService::AsyncIOService() : uv(nullptr), inboundIORequests(128), outboundIORequests(128)
   {
      eventDispatcher = flair::make_shared<flair::events::EventDispatcher>();
      
      ready = false;
      quit = false;
      
      thread = std::thread([this]() { this->eventLoop(); });
   }
   
   AsyncIOService::~AsyncIOService()
   {
      quit = true;
      if (ready) uv_async_send(&asyncNullHandle);
      
      thread.join();
   }
   
   void AsyncIOService::enqueue(std::shared_ptr<IAsyncIORequest> request)
   {
      inboundIORequests.enqueue(request);
      
      asyncDequeueHandle.data = this;
      if (ready) uv_async_send(&asyncDequeueHandle);
   }
   
   void AsyncIOService::poll()
   {
      std::shared_ptr<IAsyncIORequest> request;
      while (outboundIORequests.try_dequeue(request)) {
         if (request->complete()) {
            dispatchEvent(flair::make_shared<AsyncIOEvent>(Event::COMPLETE, request));
         }
         else {
            dispatchEvent(flair::make_shared<AsyncIOEvent>(Event::PREPARING, request));
            enqueue(request);
         }
      }
   }
   
   void AsyncIOService::addEventListener(std::string type, std::function<void(std::shared_ptr<flair::events::Event>)> listener, bool useCapture, int32_t priority)
   {
      eventDispatcher->addEventListener(type, listener, useCapture, priority);
   }
   
   bool AsyncIOService::dispatchEvent(std::shared_ptr<flair::events::Event> event)
   {
      return eventDispatcher->dispatchEvent(event);
   }
   
   bool AsyncIOService::hasEventListener(std::string type)
   {
      return eventDispatcher->hasEventListener(type);
   }
   
   void AsyncIOService::removeEventListener(std::string type, std::function<void(std::shared_ptr<flair::events::Event>)> listener, bool useCapture)
   {
      return eventDispatcher->removeEventListener(type, listener, useCapture);
   }
   
   bool AsyncIOService::willTrigger(std::string type)
   {
      return eventDispatcher->willTrigger(type);
   }
   
   void AsyncIOService::eventLoop()
   {
      uv = (uv_loop_t*)std::malloc(sizeof(uv_loop_t));
      uv_loop_init(uv);
      
      uv_async_init(uv, &asyncNullHandle, nullptr);
      uv_async_init(uv, &asyncDequeueHandle, [](uv_async_t *handle) {
         static_cast<AsyncIOService*>(handle->data)->asyncDequeue(handle);
      });
      
      ready = true;
      while (!quit) {
         uv_run(uv, UV_RUN_ONCE);
      }
      ready = false;
      
      uv_loop_close(uv);
      std::free(uv);
      uv = nullptr;
   }
   
   void AsyncIOService::asyncDequeue(uv_async_t *handle)
   {
      std::shared_ptr<IAsyncIORequest> request;
      while (inboundIORequests.try_dequeue(request)) {
         switch (request->type()) {
               
            case IAsyncIORequest::Type::FILE_OPEN: {
               auto fileRequest = std::dynamic_pointer_cast<IAsyncFileRequest>(request);
               assert(fileRequest); if (!fileRequest) return;
               
               uv_fs_t * req = new uv_fs_t();
               req->data = this;
               pendingIORequests.insert(std::make_pair(req, request));
               
               uv_fs_open(uv, req, fileRequest->path().c_str(), O_RDONLY, S_IRUSR, [](uv_fs_t * req) {
                  auto self = static_cast<AsyncIOService*>(req->data);
                  auto asyncIORequest = self->pendingIORequests[req];
                  self->pendingIORequests.erase(req);
                  self->openFile(req, asyncIORequest);
               });
            } break;
               
            case IAsyncIORequest::Type::FILE_CLOSE: {
               auto fileRequest = std::dynamic_pointer_cast<IAsyncFileRequest>(request);
               assert(fileRequest); if (!fileRequest) return;
               
               uv_fs_t * req = new uv_fs_t();
               req->data = this;
               pendingIORequests.insert(std::make_pair(req, request));
               
               uv_fs_close(uv, req, fileRequest->handle(), [](uv_fs_t * req) {
                  auto self = static_cast<AsyncIOService*>(req->data);
                  auto asyncIORequest = self->pendingIORequests[req];
                  self->pendingIORequests.erase(req);
                  self->closeFile(req, asyncIORequest);
               });
            } break;
               
            case IAsyncIORequest::Type::FILE_STAT: break;
               
            case IAsyncIORequest::Type::FILE_DELETE: break;
               
            case IAsyncIORequest::Type::FILE_READ: {
               auto fileRequest = std::dynamic_pointer_cast<IAsyncFileRequest>(request);
               assert(fileRequest); if (!fileRequest) return;
               
               uv_fs_t * req = (uv_fs_t*)fileRequest->ptr();
               uv_buf_t iov;
               
               if (!req) {
                  fileRequest->data(new uint8_t[65536]);
                  iov = uv_buf_init((char*)fileRequest->data(), 65536);
                  pendingIOBuffers.insert(std::make_pair(request, iov));
                  
                  req = new uv_fs_t();
                  req->data = this;
                  fileRequest->ptr(req);
               }
               else {
                  iov = pendingIOBuffers.find(request)->second;
               }
               pendingIORequests.insert(std::make_pair(req, request));
               
               uv_fs_read(uv, req, fileRequest->handle(), &iov, 1, -1, [](uv_fs_t * req) {
                  auto self = static_cast<AsyncIOService*>(req->data);
                  auto asyncIORequest = self->pendingIORequests[req];
                  self->pendingIORequests.erase(req);
                  self->readFile(req, asyncIORequest);
               });
            } break;
               
            case IAsyncIORequest::Type::FILE_WRITE: break;
            default: break;
         }
      }
   }
   
   void AsyncIOService::openFile(uv_fs_t * req, std::shared_ptr<IAsyncIORequest> asyncIORequest)
   {
      auto fileRequest = std::dynamic_pointer_cast<IAsyncFileRequest>(asyncIORequest);
      if (req->result == -1) {
         fileRequest->error(-1);
      }
      else {
         fileRequest->handle(req->result);
      }
      fileRequest->complete(true);
      
      uv_fs_req_cleanup(req); delete req;
      outboundIORequests.enqueue(asyncIORequest);
   }
   
   void AsyncIOService::readFile(uv_fs_t * req, std::shared_ptr<IAsyncIORequest> asyncIORequest)
   {
      auto fileRequest = std::dynamic_pointer_cast<IAsyncFileRequest>(asyncIORequest);
      if (req->result > 0) {
         fileRequest->length(req->result);
      }
      else if (req->result < 0) {
         fileRequest->error(-1);
      }
      else {
         pendingIOBuffers.erase(asyncIORequest);
         
         uv_fs_req_cleanup(req); delete req;
         fileRequest->ptr(nullptr);
         delete fileRequest->data();
         delete fileRequest->data(nullptr);
         
         fileRequest->complete(true);
      }
   
      outboundIORequests.enqueue(asyncIORequest);
   }
   
   void AsyncIOService::writeFile(uv_fs_t * req, std::shared_ptr<IAsyncIORequest> asyncIORequest)
   {
      auto fileRequest = std::dynamic_pointer_cast<IAsyncFileRequest>(asyncIORequest);
      fileRequest->complete(true);
      
      uv_fs_req_cleanup(req); delete req;
      outboundIORequests.enqueue(asyncIORequest);
   }
   
   void AsyncIOService::closeFile(uv_fs_t * req, std::shared_ptr<IAsyncIORequest> asyncIORequest)
   {
      auto fileRequest = std::dynamic_pointer_cast<IAsyncFileRequest>(asyncIORequest);
      if (req->result == -1) {
         fileRequest->error(-1);
      }

      fileRequest->handle(-1);
      fileRequest->complete(true);
      
      uv_fs_req_cleanup(req); delete req;
      outboundIORequests.enqueue(asyncIORequest);
   }
   
   
// AsyncIORequest
   
   
   AsyncIORequest::AsyncIORequest(IAsyncIORequest::Type type) : _type(type), _error(0), _complete(false), _ptr(nullptr)
   {
      
   }
   
   AsyncIORequest::~AsyncIORequest()
   {
      
   }
   
   IAsyncIORequest::Type AsyncIORequest::type()
   {
      return _type;
   }
   
   int AsyncIORequest::error()
   {
      return _error;
   }
   
   int AsyncIORequest::error(int value)
   {
      return _error = value;
   }
   
   bool AsyncIORequest::complete()
   {
      return _complete;
   }
   
   bool AsyncIORequest::complete(bool value)
   {
      return _complete = value;
   }
   
   void * AsyncIORequest::ptr()
   {
      return _ptr;
   }
   
   void * AsyncIORequest::ptr(void * ptr)
   {
      return _ptr = ptr;
   }

}}}}
