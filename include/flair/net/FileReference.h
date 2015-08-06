#ifndef flair_net_FileReference_h
#define flair_net_FileReference_h

#include "flair/flair.h"
#include "flair/events/EventDispatcher.h"
#include "flair/utils/ByteArray.h"

#include <chrono>
#include <ctime>

namespace flair { namespace desktop { class NativeApplication; } }
namespace flair { namespace internal { namespace services { class IFileService; } } }

namespace flair {
namespace net {
   
   class FileReference : public flair::events::EventDispatcher
   {
      friend class flair::allocator;
      
   protected:
      FileReference();
      
   public:
      ~FileReference();
      
   // Properties
   public:
      std::chrono::system_clock::time_point creationDate();
      
      std::shared_ptr<flair::utils::ByteArray> data();
      
      std::string extension();
      
      std::chrono::system_clock::time_point modificationDate();
      
      std::string name();
      
      size_t size();
      
   // Methods
   public:
      void load();
      
      void lookup();
      
      // TODO: browse, upload, download, save
      
   protected:
      int _state;
      std::string _path;
      std::shared_ptr<flair::utils::ByteArray> _data;
      std::time_t _creationDate;
      std::time_t _modificationDate;
      size_t _size;
      bool _exists;
      bool _isDirectory;
      
   // Internal
   protected:
      friend class flair::desktop::NativeApplication;
      static flair::internal::services::IFileService * fileService;
   };
   
}}

#endif
