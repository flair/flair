#include "flair/filesystem/File.h"
#include "flair/internal/services/IFileService.h"

#include <cassert>

namespace flair {
namespace filesystem {
   
   File::File(std::string path)
   {
      _path = path;
   }
   
   File::~File()
   {
      
   }
   
   std::shared_ptr<File> File::applicationDirectory()
   {
      assert(fileService);
      return flair::make_shared<File>(fileService->applicationDirectory());
   }
   
   std::string File::seperator()
   {
      assert(fileService);
      return fileService->seperator();
   }

}}
