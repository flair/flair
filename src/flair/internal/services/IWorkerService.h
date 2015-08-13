#ifndef flair_internal_services_IWorkerService_h
#define flair_internal_services_IWorkerService_h

#include "flair/net/FileReference.h"
#include "flair/internal/services/IAsyncIOService.h"

#include <functional>

namespace flair {
namespace internal {
namespace services {
   
   class IWorkerService
   {
   public:
      virtual void init(IAsyncIOService * asyncIOService) = 0;
      
      virtual void execute(std::function<std::shared_ptr<IAsyncWorkerRequest::IWorkerResult>()> worker, std::function<void(std::shared_ptr<IAsyncWorkerRequest>)> callback) = 0;
   };
   
}}}

#endif
