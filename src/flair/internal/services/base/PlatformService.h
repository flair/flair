#ifndef flair_internal_services_base_PlatformService_h
#define flair_internal_services_base_PlatformService_h

#include "flair/internal/services/IPlatformService.h"

namespace flair {
namespace internal {
namespace services {
namespace base {
   
   class PlatformService : public IPlatformService
   {
   public:
      std::string urlToPath(std::string url) override;
      
      std::string pathToUrl(std::string path) override;
   };

}}}}

#endif
