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
      auto appPrefix = applicationDirectory() + directorySeperator();
      auto appStoragePrefix = applicationStorageDirectory() + directorySeperator();
      
      if (path.find(appStoragePrefix) == 0) {
         auto rootUrl = std::string("app-storage:/");
         auto relativeUrl = path.substr(appStoragePrefix.length(), path.length() - appStoragePrefix.length());
         std::replace(relativeUrl.begin(), relativeUrl.end(), directorySeperator()[0], '/');
         
         return rootUrl + relativeUrl;
      }
      else if (path.find(appPrefix) == 0) {
         auto rootUrl = std::string("app:/");
         auto relativeUrl = path.substr(appPrefix.length(), path.length() - appPrefix.length());
         std::replace(relativeUrl.begin(), relativeUrl.end(), directorySeperator()[0], '/');
         
         return rootUrl + relativeUrl;
      }
      else {
         auto rootUrl = std::string("file:///");
         auto relativeUrl = path;
         std::replace(relativeUrl.begin(), relativeUrl.end(), directorySeperator()[0], '/');
         
         return rootUrl + relativeUrl;
      }
      
      return path;
   }
   
}}}}
