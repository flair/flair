#ifndef flair_internal_services_mac_PlatformService_h
#define flair_internal_services_mac_PlatformService_h

#include "flair/internal/services/IPlatformService.h"

namespace flair {
namespace internal {
namespace services {
namespace mac {
   
   class PlatformService : public IPlatformService
   {
   public:
      std::string os() override;
      
      std::string language() override;
      
      std::vector<std::string> languages() override;
      
      std::string applicationDirectory() override;
      
      std::string applicationStorageDirectory() override;
      
      std::string cacheDirectory() override;
      
      std::string desktopDirectory() override;
      
      std::string documentsDirectory() override;
      
      std::string userDirectory() override;
      
      std::string directorySeperator() override;
   };
   
}}}}

#endif
