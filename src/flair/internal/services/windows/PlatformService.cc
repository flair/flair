#include "flair/internal/services/windows/PlatformService.h"

#include <shlobj.h>

namespace flair {
namespace internal {
namespace services {
namespace windows {

   std::string PlatformService::os()
   {
      return "";
   }
   
   std::string PlatformService::language()
   {
      return "";
   }
   
   std::vector<std::string> PlatformService::languages()
   {
      return std::vector<std::string>();
   }
   
   std::string PlatformService::applicationDirectory()
   {
      return "";
   }
   
   std::string PlatformService::applicationStorageDirectory()
   {
      return "";
   }
   
   std::string PlatformService::cacheDirectory()
   {
      return "";
   }
   
   std::string PlatformService::desktopDirectory()
   {
      return "";
   }
   
   std::string PlatformService::documentsDirectory()
   {
      return "";
   }
   
   std::string PlatformService::userDirectory()
   {
      return "";
   }
   
   std::string PlatformService::directorySeperator()
   {
      return "\\";
   }
   
}}}}
