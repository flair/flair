#include "flair/internal/services/uv/WorkerService.h"

namespace flair {
namespace internal {
namespace services {
namespace uv {
   
   using flair::events::Event;
   
   WorkerService::WorkerService() : asyncIOService(nullptr)
   {
      
   }
   
   WorkerService::~WorkerService()
   {
      
   }
   
   void WorkerService::init(IAsyncIOService * asyncIOService)
   {
      this->asyncIOService = asyncIOService;
      asyncIOService->addEventListener(Event::COMPLETE, [this](std::shared_ptr<flair::events::Event> e) { onAsyncIORequest(e); });
   }
   
   void WorkerService::execute(std::function<std::shared_ptr<IAsyncWorkerRequest::IWorkerResult>()> worker, std::function<void(std::shared_ptr<IAsyncWorkerRequest>)> callback)
   {
      auto request = std::make_shared<AsyncWorkerRequest>();
      asyncCallbacks.insert(std::make_pair(request, callback));
      
      request->worker(worker);
      asyncIOService->enqueue(std::static_pointer_cast<IAsyncIORequest>(request));
   }
   
   void WorkerService::onAsyncIORequest(std::shared_ptr<flair::events::Event> event)
   {
      auto asyncEvent = std::dynamic_pointer_cast<AsyncIOEvent>(event);
      auto asyncRequest = asyncEvent->request();
      auto workerRequest = std::dynamic_pointer_cast<AsyncWorkerRequest>(asyncRequest);
      if (!workerRequest) return;
      
      std::function<void(std::shared_ptr<IAsyncWorkerRequest>)> callback = nullptr;
      auto it = asyncCallbacks.find(workerRequest);
      assert(it != asyncCallbacks.end());
      if (it != asyncCallbacks.end()) {
         callback = it->second;
      }
      
      if (!callback) return;
      if (Event::COMPLETE == event->type()) {
         asyncCallbacks.erase(it);
         callback(workerRequest);
      }
   }
   
   
   // AsyncWorkerRequest
   
   
   AsyncWorkerRequest::AsyncWorkerRequest() : _type(IAsyncIORequest::Type::WORKER), _id(SIZE_MAX), _error(0), _complete(false),
      _result(nullptr), _worker(nullptr)
   {
      
   }
   std::shared_ptr<IAsyncWorkerRequest::IWorkerResult> AsyncWorkerRequest::result()
   {
      return _result;
   }
   
   std::shared_ptr<IAsyncWorkerRequest::IWorkerResult> AsyncWorkerRequest::result(std::shared_ptr<IWorkerResult> value)
   {
      return _result = value;
   }
   
   std::function<std::shared_ptr<IAsyncWorkerRequest::IWorkerResult>()> AsyncWorkerRequest::worker()
   {
      return _worker;
   }
   
   std::function<std::shared_ptr<IAsyncWorkerRequest::IWorkerResult>()> AsyncWorkerRequest::worker(std::function<std::shared_ptr<IWorkerResult>()> value)
   {
      return _worker = value;
   }
   
   IAsyncIORequest::Type AsyncWorkerRequest::type()
   {
      return _type;
   }
   
   size_t AsyncWorkerRequest::id()
   {
      return _id;
   }
   
   size_t AsyncWorkerRequest::id(size_t value)
   {
      return _id = value;
   }
   
   int AsyncWorkerRequest::error()
   {
      return _error;
   }
   int AsyncWorkerRequest::error(int value)
   {
      return _error = value;
   }
   
   bool AsyncWorkerRequest::complete()
   {
      return _complete;
   }
   
   bool AsyncWorkerRequest::complete(bool value)
   {
      return _complete = value;
   }

}}}}
