#ifndef flair_internal_services_uv_AsyncWorkerService_h
#define flair_internal_services_uv_AsyncWorkerService_h

#include "flair/flair.h"
#include "flair/net/FileReference.h"
#include "flair/internal/services/IAsyncIOService.h"
#include "flair/internal/ConcurrentQueue.h"

#include "uv.h"

#include <thread>
#include <atomic>
#include <vector>
#include <stack>
#include <map>

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
      
      size_t id() override;
      size_t id(size_t value) override;
      
      int error() override;
      int error(int value) override;
      
      bool complete() override;
      bool complete(bool value) override;
      
   protected:
      IAsyncIORequest::Type _type;
      size_t _id;
      int _error;
      bool _complete;
      void * _ptr;
   };
   
   
   class AsyncIOService : public IAsyncIOService
   {
   public:
      struct Context
      {
         union {
            uv_fs_event fs_event;
            uv_handle_t handle;
            uv_stream_t stream;
            uv_tcp_t tcp;
            uv_udp_t udp;
         }; // handles
         
         union {
            uv_req_t req;
            uv_connect_t connect;
            uv_write_t write;
            uv_udp_send_t udp_send;
            uv_fs_t fs;
         }; // requests
         
         uv_buf_t buffer;
      };
      
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
      
      std::vector<Context> contextPool;
      std::stack<uint32_t> contextStack;
      
      std::map<uv_fs_t *, std::shared_ptr<IAsyncIORequest>> pendingIORequests;
      
   protected:
      uint32_t popContextId();
      void pushContextId(uint32_t id);
      
   private:
      void eventLoop();
      
      uv_async_t asyncDequeueHandle;
      void asyncDequeue(uv_async_t *handle);
      
      void statFile(uv_fs_t* req, std::shared_ptr<IAsyncIORequest> asyncIORequest);
      void openFile(uv_fs_t* req, std::shared_ptr<IAsyncIORequest> asyncIORequest);
      void readFile(uv_fs_t* req, std::shared_ptr<IAsyncIORequest> asyncIORequest);
      void writeFile(uv_fs_t* req, std::shared_ptr<IAsyncIORequest> asyncIORequest);
      void closeFile(uv_fs_t* req, std::shared_ptr<IAsyncIORequest> asyncIORequest);
   };
   
}}}}

#endif
