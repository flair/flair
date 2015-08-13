#ifndef flair_internal_services_IPlatformService_h
#define flair_internal_services_IPlatformService_h

#include <string>
#include <vector>

namespace flair {
namespace internal {
namespace services {
   
   class IPlatformService
   {
   public:
      virtual std::string os() = 0;
      
      virtual std::string userAgent() = 0;
      
      virtual std::string language() = 0;
      
      virtual std::vector<std::string> languages() = 0;
      
      virtual std::string applicationDirectory() = 0;
      
      virtual std::string applicationStorageDirectory() = 0;
      
      virtual std::string cacheDirectory() = 0;
      
      virtual std::string desktopDirectory() = 0;
      
      virtual std::string documentsDirectory() = 0;
      
      virtual std::string userDirectory() = 0;
      
      virtual std::string directorySeperator() = 0;
      
      virtual std::string urlToPath(std::string url) = 0;
      
      virtual std::string pathToUrl(std::string path) = 0;

   };
   
}}}

#endif
