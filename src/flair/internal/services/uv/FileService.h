#ifndef flair_internal_services_FileService_h
#define flair_internal_services_FileService_h

#include "flair/net/FileReference.h"
#include "flair/internal/services/IFileService.h"
#include "flair/internal/services/uv/AsyncIOService.h"

#include <map>
#include <functional>

namespace flair {
namespace internal {
namespace services {
namespace uv {
   
   class AsyncFileRequest : public IAsyncFileRequest
   {
   public:
      AsyncFileRequest(IAsyncIORequest::Type type, std::shared_ptr<flair::net::FileReference> fileReference);
      
   public:
      std::shared_ptr<flair::net::FileReference> fileReference();
      
      std::string path() override;
      std::string path(std::string value) override;
      
      FileHandle handle() override;
      FileHandle handle(FileHandle value) override;
      
      uint32_t flags() override;
      uint32_t flags(uint32_t value) override;
      
      FileStats stats() override;
      FileStats stats(FileStats value) override;
      
      uint8_t * data() override;
      uint8_t * data(uint8_t * value) override;
      
      size_t offset() override;
      size_t offset(size_t value) override;
      
      size_t length() override;
      size_t length(size_t value) override;
      
      Type type() override;
      
      int error() override;
      int error(int value) override;
      
      bool complete() override;
      bool complete(bool value) override;
      
   protected:
      Type _type;
      int _error;
      bool _complete;
      std::shared_ptr<flair::net::FileReference> _fileReference;
      std::string _path;
      FileHandle _handle;
      uint32_t _flags;
      FileStats _stats;
      uint8_t * _data;
      size_t _offset;
      size_t _length;
   };
   
   
   class FileService : public IFileService
   {
   public:
      FileService();
      virtual ~FileService();
      
   public:
      void init(IAsyncIOService * asyncIOService) override;
      
      void open(std::string path, uint32_t flags, std::shared_ptr<flair::net::FileReference> fileReference, std::function<void(std::shared_ptr<IAsyncFileRequest>)> callback) override;
      
      void close(IAsyncFileRequest::FileHandle file, std::shared_ptr<flair::net::FileReference> fileReference, std::function<void(std::shared_ptr<IAsyncFileRequest>)> callback) override;
      
      void stat(IAsyncFileRequest::FileHandle file, std::shared_ptr<flair::net::FileReference> fileReference, std::function<void(std::shared_ptr<IAsyncFileRequest>)> callback) override;
      
      void read(IAsyncFileRequest::FileHandle file, std::shared_ptr<flair::net::FileReference> fileReference, std::function<void(std::shared_ptr<IAsyncFileRequest>)> callback) override;
      
      void write(IAsyncFileRequest::FileHandle file, uint8_t * buffer, uint8_t length, std::shared_ptr<flair::net::FileReference> fileReference, std::function<void(std::shared_ptr<IAsyncFileRequest>)> callback) override;
      
      std::string applicationDirectory() override;
      
      std::string applicationStorageDirectory() override;
      
      std::string cacheDirectory() override;
      
      std::string desktopDirectory() override;
      
      std::string documentsDirectory() override;
      
      std::string userDirectory() override;
      
   protected:
      void onAsyncIORequest(std::shared_ptr<flair::events::Event> event);
      
   protected:
      IAsyncIOService * asyncIOService;
      std::map<std::shared_ptr<flair::net::FileReference>, std::function<void(std::shared_ptr<IAsyncFileRequest>)>> asyncCallbacks;
   };
   
}}}}


#endif
