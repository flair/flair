#include "flair/internal/services/uv/FileService.h"

namespace flair {
namespace internal {
namespace services {
namespace uv {
   
   using flair::events::Event;
   using flair::net::FileReference;
   
   
   FileService::FileService() : asyncIOService(nullptr)
   {
      
   }
   
   FileService::~FileService()
   {
      
   }
   
   void FileService::init(IAsyncIOService * asyncIOService)
   {
      this->asyncIOService = asyncIOService;
      asyncIOService->addEventListener(Event::INIT, [this](std::shared_ptr<flair::events::Event> e) { onAsyncIORequest(e); });
      asyncIOService->addEventListener(Event::PREPARING, [this](std::shared_ptr<flair::events::Event> e) { onAsyncIORequest(e); });
      asyncIOService->addEventListener(Event::COMPLETE, [this](std::shared_ptr<flair::events::Event> e) { onAsyncIORequest(e); });
   }
   
   void FileService::stat(std::string path, std::shared_ptr<flair::net::FileReference> fileReference, std::function<void(std::shared_ptr<IAsyncFileRequest>)> callback)
   {
      asyncCallbacks.insert(std::make_pair(fileReference, callback));
      
      auto request = std::make_shared<AsyncFileRequest>(IAsyncIORequest::Type::FILE_STAT, fileReference);
      request->path(path);
      asyncIOService->enqueue(std::static_pointer_cast<IAsyncIORequest>(request));
   }
   
   void FileService::open(std::string path, uint32_t flags, std::shared_ptr<flair::net::FileReference> fileReference, std::function<void(std::shared_ptr<IAsyncFileRequest>)> callback)
   {
      asyncCallbacks.insert(std::make_pair(fileReference, callback));
      
      auto request = std::make_shared<AsyncFileRequest>(IAsyncIORequest::Type::FILE_OPEN, fileReference);
      request->path(path);
      request->flags(flags);
      asyncIOService->enqueue(std::static_pointer_cast<IAsyncIORequest>(request));
   }
   
   void FileService::close(IAsyncFileRequest::FileHandle file, std::shared_ptr<flair::net::FileReference> fileReference, std::function<void(std::shared_ptr<IAsyncFileRequest>)> callback)
   {
      asyncCallbacks.insert(std::make_pair(fileReference, callback));
      
      auto request = std::make_shared<AsyncFileRequest>(IAsyncIORequest::Type::FILE_CLOSE, fileReference);
      request->handle(file);
      asyncIOService->enqueue(std::static_pointer_cast<IAsyncIORequest>(request));
   }
   
   void FileService::read(IAsyncFileRequest::FileHandle file, std::shared_ptr<flair::net::FileReference> fileReference, std::function<void(std::shared_ptr<IAsyncFileRequest>)> callback)
   {
      asyncCallbacks.insert(std::make_pair(fileReference, callback));
      
      auto request = std::make_shared<AsyncFileRequest>(IAsyncIORequest::Type::FILE_READ, fileReference);
      request->handle(file);
      asyncIOService->enqueue(std::static_pointer_cast<IAsyncIORequest>(request));
   }
   
   void FileService::write(IAsyncFileRequest::FileHandle file, uint8_t * buffer, uint8_t length, std::shared_ptr<flair::net::FileReference> fileReference, std::function<void(std::shared_ptr<IAsyncFileRequest>)> callback)
   {
      asyncCallbacks.insert(std::make_pair(fileReference, callback));
      
      auto request = std::make_shared<AsyncFileRequest>(IAsyncIORequest::Type::FILE_WRITE, fileReference);
      request->handle(file);
      asyncIOService->enqueue(std::static_pointer_cast<IAsyncIORequest>(request));
   }
   
   void FileService::onAsyncIORequest(std::shared_ptr<flair::events::Event> event)
   {
      auto asyncEvent = std::dynamic_pointer_cast<AsyncIOEvent>(event);
      auto asyncRequest = asyncEvent->request();
      auto fileRequest = std::dynamic_pointer_cast<AsyncFileRequest>(asyncRequest);
      if (!fileRequest) return;
      
      std::function<void(std::shared_ptr<IAsyncFileRequest>)> callback = nullptr;
      auto fileReference = fileRequest->fileReference();
      auto it = asyncCallbacks.find(fileReference);
      assert(it != asyncCallbacks.end());
      if (it != asyncCallbacks.end()) {
         callback = it->second;
      }
      
      if (!callback) return;
      if (Event::PREPARING == event->type()) {
         callback(fileRequest);
      }
      else if (Event::COMPLETE == event->type()) {
         asyncCallbacks.erase(it);
         callback(fileRequest);
      }
   }
   
   
// AsyncFileRequest
   
   
   AsyncFileRequest::AsyncFileRequest(IAsyncIORequest::Type type, std::shared_ptr<FileReference> fileReference) : _type(type), _id(SIZE_MAX), _error(0), _complete(false), _fileReference(fileReference), _path(""), _handle(-1), _flags(0), _data(nullptr), _offset(0), _length(0)
   {
      _stats.created = std::time(nullptr);
      _stats.modified = std::time(nullptr);
      _stats.size = 0;
   }
   
   std::shared_ptr<FileReference> AsyncFileRequest::fileReference()
   {
      return _fileReference;
   }
   
   std::string AsyncFileRequest::path()
   {
      return _path;
   }
   
   std::string AsyncFileRequest::path(std::string value)
   {
      return _path = value;
   }
   
   IAsyncFileRequest::FileHandle AsyncFileRequest::handle()
   {
      return _handle;
   }
   
   IAsyncFileRequest::FileHandle AsyncFileRequest::handle(FileHandle value)
   {
      return _handle = value;
   }
   
   uint32_t AsyncFileRequest::flags()
   {
      return _flags;
   }
   
   uint32_t AsyncFileRequest::flags(uint32_t value)
   {
      return _flags = value;
   }
   
   IAsyncFileRequest::FileStats AsyncFileRequest::stats()
   {
      return _stats;
   }
   
   IAsyncFileRequest::FileStats AsyncFileRequest::stats(FileStats value)
   {
      return _stats = value;
   }
   
   uint8_t * AsyncFileRequest::data()
   {
      return _data;
   }
   
   uint8_t * AsyncFileRequest::data(uint8_t * value)
   {
      return _data = value;
   }
   
   size_t AsyncFileRequest::offset()
   {
      return _offset;
   }
   
   size_t AsyncFileRequest::offset(size_t value)
   {
      return _offset = value;
   }
   
   size_t AsyncFileRequest::length()
   {
      return _length;
   }
   
   size_t AsyncFileRequest::length(size_t value)
   {
      return _length = value;
   }
   
   IAsyncIORequest::Type AsyncFileRequest::type()
   {
      return _type;
   }
   
   size_t AsyncFileRequest::id()
   {
      return _id;
   }
   
   size_t AsyncFileRequest::id(size_t value)
   {
      return _id = value;
   }
   
   int AsyncFileRequest::error()
   {
      return _error;
   }
   
   int AsyncFileRequest::error(int value)
   {
      return _error = value;
   }
   
   bool AsyncFileRequest::complete()
   {
      return _complete;
   }
   
   bool AsyncFileRequest::complete(bool value)
   {
      return _complete = value;
   }

}}}}