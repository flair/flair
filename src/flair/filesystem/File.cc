#include "flair/filesystem/File.h"
#include "flair/internal/services/IFileService.h"
#include "flair/internal/services/IPlatformService.h"

#include <cassert>

namespace flair {
namespace filesystem {
   
   File::File(std::string path)
   {
      assert(platformService);
      _path = platformService->urlToPath(path);
   }
   
   File::~File()
   {
      
   }
   
   bool File::exists()
   {
      return _exists;
   }
   
   bool File::isDirectory()
   {
      return _isDirectory;
   }
   
   std::string File::url()
   {
      assert(platformService);
      return platformService->pathToUrl(_path);
   }
   
   std::shared_ptr<File> File::applicationDirectory()
   {
      assert(platformService);
      return flair::make_shared<File>(platformService->applicationDirectory());
   }
   
   std::shared_ptr<File> File::applicationStorageDirectory()
   {
      assert(platformService);
      return flair::make_shared<File>(platformService->applicationStorageDirectory());
   }
   
   std::shared_ptr<File> File::cacheDirectory()
   {
      assert(platformService);
      return flair::make_shared<File>(platformService->cacheDirectory());
   }
   
   std::shared_ptr<File> File::desktopDirectory()
   {
      assert(platformService);
      return flair::make_shared<File>(platformService->desktopDirectory());
   }
   
   std::shared_ptr<File> File::documentsDirectory()
   {
      assert(platformService);
      return flair::make_shared<File>(platformService->documentsDirectory());
   }
   
   std::shared_ptr<File> File::userDirectory()
   {
      assert(platformService);
      return flair::make_shared<File>(platformService->userDirectory());
   }
   
   std::string File::seperator()
   {
      assert(platformService);
      return platformService->directorySeperator();
   }

}}
