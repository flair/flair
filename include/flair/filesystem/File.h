#ifndef flair_filesystem_File_h
#define flair_filesystem_File_h

#include "flair/flair.h"
#include "flair/net/FileReference.h"

namespace flair {
namespace filesystem {
   
   class File : public flair::net::FileReference
   {
      friend class flair::allocator;
      
   protected:
      File(std::string path = "");
      
   public:
      virtual ~File();
   
   // Properties
   public:
      bool exists();
      
      bool isDirectory();
      
      std::string url();
      
   public:
      static std::shared_ptr<File> applicationDirectory();
      
      static std::shared_ptr<File> applicationStorageDirectory();
      
      static std::shared_ptr<File> cacheDirectory();
      
      static std::shared_ptr<File> desktopDirectory();
      
      static std::shared_ptr<File> documentsDirectory();
      
      static std::shared_ptr<File> userDirectory();
      
      static std::string seperator();
   };
   
}}

#endif
