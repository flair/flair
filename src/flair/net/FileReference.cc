#include "flair/net/FileReference.h"
#include "flair/internal/services/IAsyncIOService.h"
#include "flair/internal/services/IFileService.h"

#include <cassert>
#include <ctime>

namespace {
   struct FileState {
      enum { FILE_EMPTY, FILE_LOADING, FILE_LOADED };
   };
}

namespace flair {
namespace net {
   
   using namespace flair::internal::services;
   using namespace flair::events;
   
   flair::internal::services::IFileService * FileReference::fileService = nullptr;
   
   FileReference::FileReference() : _state(FileState::FILE_EMPTY), _path(""), _data(nullptr), _exists(false), _isDirectory(false), _size(0), _creationDate(std::time(nullptr)), _modificationDate(std::time(nullptr))
   {
      
   }
   
   FileReference::~FileReference()
   {
      
   }
   
   std::chrono::system_clock::time_point FileReference::creationDate()
   {
      return std::chrono::system_clock::from_time_t(_creationDate);
   }
   
   std::shared_ptr<flair::utils::ByteArray> FileReference::data()
   {
      if (_state != FileState::FILE_LOADED) return nullptr;
      
      return _data;
   }
   
   
   std::string FileReference::extension()
   {
      return _path.substr(_path.find_last_of("."));
   }
   
   std::chrono::system_clock::time_point FileReference::modificationDate()
   {
      return std::chrono::system_clock::from_time_t(_modificationDate);
   }
   
   std::string FileReference::name()
   {
      return _path;
   }
   
   size_t FileReference::size()
   {
      return _data && _data->length() > _size ? _data->length() : _size;
   }
   
   void FileReference::load()
   {
      assert(fileService);
      
      // Return if already loading
      if (_state == FileState::FILE_LOADING) return;
      _state = FileState::FILE_LOADING;
      
      // Create or reset the data buffer
      if (!_data) {
         _data = flair::make_shared<utils::ByteArray>();
      }
      else {
         _data->position(0);
      }
      
      // Stat the file
      fileService->stat(_path, std::static_pointer_cast<FileReference>(shared_from_this()), [this](std::shared_ptr<IAsyncFileRequest> request) {
         auto stats = request->stats();
         _exists = stats.exists;
         if (_exists) {
            _isDirectory = stats.isDirectory;
            _size = stats.size;
            _creationDate = stats.created;
            _modificationDate = stats.modified;
         }
         
         // Bail if it doesn't exist
         if (!_exists) {
            _state = FileState::FILE_EMPTY;
            dispatchEvent(flair::make_shared<Event>(Event::ERROR));
            return;
         }
         
         dispatchEvent(flair::make_shared<Event>(Event::INIT));
         
         // Open the file
         fileService->open(_path, 0, shared<FileReference>(), [this](std::shared_ptr<IAsyncFileRequest> request) {
            if (request->error() != 0) {
               _state = FileState::FILE_EMPTY;
               dispatchEvent(flair::make_shared<Event>(Event::ERROR));
               return;
            }
            
            // If success, then read the file
            fileService->read(request->handle(), shared<FileReference>(), [this](std::shared_ptr<IAsyncFileRequest> request) {
               if (request->error() != 0) {
                  // If there was an error, ensure we close the file
                  fileService->close(request->handle(), shared<FileReference>(), [this](std::shared_ptr<IAsyncFileRequest> request) {
                     _state = FileState::FILE_EMPTY;
                     dispatchEvent(flair::make_shared<Event>(Event::ERROR));
                  });
                  return;
               }
               
               // If the request is not complete, keep reading the data into our buffer
               if (!request->complete()) {
                  _data->writeBytes(request->data(), request->offset(), request->length());
                  return;
               }
               
               // Finally, close the file
               fileService->close(request->handle(), shared<FileReference>(), [this](std::shared_ptr<IAsyncFileRequest> request) {
                  if (request->error() != 0) {
                     _state = FileState::FILE_EMPTY;
                     dispatchEvent(flair::make_shared<Event>(Event::ERROR));
                     return;
                  }
                  
                  _data->position(0);
                  _state = FileState::FILE_LOADED;
                  dispatchEvent(flair::make_shared<Event>(Event::COMPLETE));
               });
            });
         });
      });
   }
   
   void FileReference::lookup()
   {
      fileService->stat(_path, std::static_pointer_cast<FileReference>(shared_from_this()), [this](std::shared_ptr<IAsyncFileRequest> request) {
         auto stats = request->stats();
         _exists = stats.exists;
         if (_exists) {
            _isDirectory = stats.isDirectory;
            _size = stats.size;
            _creationDate = stats.created;
            _modificationDate = stats.modified;
         }
         
         if (_exists) {
            dispatchEvent(flair::make_shared<Event>(Event::INIT));
         }
         else {
            dispatchEvent(flair::make_shared<Event>(Event::ERROR));
         }
      });
   }
   
}}
