#include "flair/internal/services/base/PlatformService.h"

#include <algorithm>

namespace flair {
namespace internal {
namespace services {
namespace base {
   
   std::string PlatformService::urlToPath(std::string url)
   {
      auto filePrefix = std::string("file:///");
      auto appPrefix = std::string("app:/");
      auto appStoragePrefix = std::string("app-storage:/");
      
      if (url.find(filePrefix) == 0) {
         auto platformPath = url.substr(filePrefix.length(), url.length() - filePrefix.length());
         std::replace(platformPath.begin(), platformPath.end(), '/', directorySeperator()[0]);
         
         return platformPath;
      }
      else if (url.find(appPrefix) == 0) {
         auto platformPath = applicationDirectory() + directorySeperator();
         auto relativePath = url.substr(appPrefix.length(), url.length() - appPrefix.length());
         std::replace(relativePath.begin(), relativePath.end(), '/', directorySeperator()[0]);
         
         return platformPath + relativePath;
      }
      else if (url.find(appStoragePrefix) == 0) {
         auto platformPath = applicationStorageDirectory() + directorySeperator();
         auto relativePath = url.substr(appStoragePrefix.length(), url.length() - appStoragePrefix.length());
         std::replace(relativePath.begin(), relativePath.end(), '/', directorySeperator()[0]);
         
         return platformPath + relativePath;
      }
      
      return url;
   }
   
   std::string PlatformService::pathToUrl(std::string path)
   {
      return path;
   }
   
}}}}
