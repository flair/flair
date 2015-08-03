#ifndef flair_internal_services_IFileService_h
#define flair_internal_services_IFileService_h

#include "flair/net/FileReference.h"
#include "flair/internal/services/IAsyncIOService.h"

#include <ctime>
#include <functional>

namespace flair {
namespace internal {
namespace services {

   class IFileService
   {  
   public:
      virtual void init(IAsyncIOService * asyncIOService) = 0;
      
      virtual void open(std::string path, uint32_t flags, std::shared_ptr<flair::net::FileReference> fileReference, std::function<void(std::shared_ptr<IAsyncFileRequest>)> callback) = 0;
      
      virtual void close(IAsyncFileRequest::FileHandle file, std::shared_ptr<flair::net::FileReference> fileReference, std::function<void(std::shared_ptr<IAsyncFileRequest>)> callback) = 0;
      
      virtual void stat(IAsyncFileRequest::FileHandle file, std::shared_ptr<flair::net::FileReference> fileReference, std::function<void(std::shared_ptr<IAsyncFileRequest>)> callback) = 0;
      
      virtual void read(IAsyncFileRequest::FileHandle file, std::shared_ptr<flair::net::FileReference> fileReference, std::function<void(std::shared_ptr<IAsyncFileRequest>)> callback) = 0;
      
      virtual void write(IAsyncFileRequest::FileHandle file, uint8_t * buffer, uint8_t length, std::shared_ptr<flair::net::FileReference> fileReference, std::function<void(std::shared_ptr<IAsyncFileRequest>)> callback) = 0;
      
      virtual std::string applicationDirectory() = 0;
      
      virtual std::string applicationStorageDirectory() = 0;
      
      virtual std::string cacheDirectory() = 0;
      
      virtual std::string desktopDirectory() = 0;
      
      virtual std::string documentsDirectory() = 0;
      
      virtual std::string userDirectory() = 0;
   };
   
}}}

#endif
