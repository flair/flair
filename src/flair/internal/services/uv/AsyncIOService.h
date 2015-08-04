#ifndef flair_internal_services_uv_AsyncWorkerService_h
#define flair_internal_services_uv_AsyncWorkerService_h

#include "flair/flair.h"
#include "flair/net/FileReference.h"
#include "flair/internal/services/IAsyncIOService.h"
#include "flair/internal/ConcurrentQueue.h"

#include "uv.h"

#include <thread>
#include <atomic>
#include <unordered_map>

namespace flair {
namespace internal {
namespace services {
namespace uv {
   
   class AsyncIORequest : public IAsyncIORequest
   {
   public:
      AsyncIORequest(IAsyncIORequest::Type type);
      ~AsyncIORequest();

   // Properties
   public:
      IAsyncIORequest::Type type() override;
      
      int error() override;
      int error(int value) override;
      
      bool complete() override;
      bool complete(bool value) override;
      
      void * ptr() override;
      void * ptr(void * ptr) override;
      
   protected:
      IAsyncIORequest::Type _type;
      int _error;
      bool _complete;
      void * _ptr;
   };
   
   
   class AsyncIOService : public IAsyncIOService
   {
   public:
      AsyncIOService();
      ~AsyncIOService();
      
   public:
      void enqueue(std::shared_ptr<IAsyncIORequest> request) override;
      
      void poll() override;
      
   public:
      void addEventListener(std::string type, std::function<void(std::shared_ptr<flair::events::Event>)> listener, bool useCapture = false, int32_t priority = 0) override;
      
      bool dispatchEvent(std::shared_ptr<flair::events::Event> event) override;
      
      bool hasEventListener(std::string type) override;
      
      void removeEventListener(std::string type, std::function<void(std::shared_ptr<flair::events::Event>)> listener, bool useCapture = false) override;
      
      bool willTrigger(std::string type) override;
      
   protected:
      std::shared_ptr<flair::events::EventDispatcher> eventDispatcher;
      
      std::atomic_bool ready;
      std::atomic_bool quit;
      std::thread thread;
      
      uv_async_t asyncNullHandle;
      uv_loop_t *uv;
      
      ConcurrentQueue<std::shared_ptr<IAsyncIORequest>> inboundIORequests;
      ConcurrentQueue<std::shared_ptr<IAsyncIORequest>> outboundIORequests;
      
      std::map<uv_fs_t*, std::shared_ptr<IAsyncIORequest>> pendingIORequests;
      std::map<std::shared_ptr<IAsyncIORequest>, uv_buf_t> pendingIOBuffers;
      
   private:
      void eventLoop();
      
      uv_async_t asyncDequeueHandle;
      void asyncDequeue(uv_async_t *handle);
      
      void openFile(uv_fs_t* req, std::shared_ptr<IAsyncIORequest> asyncIORequest);
      void readFile(uv_fs_t* req, std::shared_ptr<IAsyncIORequest> asyncIORequest);
      void writeFile(uv_fs_t* req, std::shared_ptr<IAsyncIORequest> asyncIORequest);
      void closeFile(uv_fs_t* req, std::shared_ptr<IAsyncIORequest> asyncIORequest);
   };
   
}}}}

#endif
