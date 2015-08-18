#ifndef flair_internal_services_uv_WorkerService_h
#define flair_internal_services_uv_WorkerService_h

#include "flair/net/FileReference.h"
#include "flair/internal/services/IWorkerService.h"

#include <map>
#include <memory>
#include <functional>

namespace flair {
namespace internal {
namespace services {
namespace uv {
   
   class AsyncWorkerRequest : public IAsyncWorkerRequest
   {
   public:
      AsyncWorkerRequest();
      
   public:
      std::shared_ptr<IWorkerResult> result() override;
      std::shared_ptr<IWorkerResult> result(std::shared_ptr<IWorkerResult> value) override;
      
      std::function<std::shared_ptr<IWorkerResult>()> worker() override;
      std::function<std::shared_ptr<IWorkerResult>()> worker(std::function<std::shared_ptr<IWorkerResult>()> callable) override;
      
      Type type() override;
      
      size_t id() override;
      size_t id(size_t value) override;
      
      int error() override;
      int error(int value) override;
      
      bool complete() override;
      bool complete(bool value) override;
      
   protected:
      Type _type;
      size_t _id;
      int _error;
      bool _complete;
      std::shared_ptr<IWorkerResult> _result;
      std::function<std::shared_ptr<IWorkerResult>()> _worker;
      
   };
   
   
   class WorkerService : public IWorkerService
   {
      
   public:
      WorkerService();
      virtual ~WorkerService();
      
   public:
      void init(IAsyncIOService * asyncIOService) override;
      
      void execute(std::function<std::shared_ptr<IAsyncWorkerRequest::IWorkerResult>()> worker, std::function<void(std::shared_ptr<IAsyncWorkerRequest>)> callback) override;
      
   protected:
      void onAsyncIORequest(std::shared_ptr<flair::events::Event> event);
      
   protected:
      IAsyncIOService * asyncIOService;
      std::map<std::shared_ptr<AsyncWorkerRequest>, std::function<void(std::shared_ptr<IAsyncWorkerRequest>)>> asyncCallbacks;
   };
   
}}}}


#endif
