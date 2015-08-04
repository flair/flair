#ifndef flair_internal_services_IAsyncIOService_h
#define flair_internal_services_IAsyncIOService_h

#include "flair/flair.h"
#include "flair/events/EventDispatcher.h"
#include "flair/events/Event.h"

namespace flair {
namespace internal {
namespace services {
   
   class IAsyncIORequest
   {
   // Types
   public:
      enum class Type {
         FILE_OPEN,
         FILE_CLOSE,
         FILE_READ,
         FILE_WRITE,
         FILE_STAT,
         FILE_RENAME,
         FILE_DELETE,
         FILE_DIR_REMOVE,
         FILE_DIR_MAKE,
         FILE_DIR_MAKE_TEMP,
         FILE_DIR_SCAN
      };
      
   // Properties
   public:
      virtual Type type() = 0;
      
      virtual int error() = 0;
      virtual int error(int value) = 0;
      
      virtual bool complete() = 0;
      virtual bool complete(bool value) = 0;
      
      virtual void * ptr() = 0;
      virtual void * ptr(void * ptr) = 0;
      
   };
   
   class IAsyncFileRequest : public IAsyncIORequest
   {
   public:
      typedef size_t FileHandle;
      
   public:
      struct FileStats
      {
         uint64_t size;
         std::time_t created;
         std::time_t modified;
      };
      
   public:
      enum {
         FILE_READ_ONLY = 0x01,
         FILE_WRITE_ONLY = 0x02,
         FILE_READ_WRITE = 0x04,
         FILE_CREATE = 0x08,
         FILE_APPEND = 0x10,
         FILE_TRUNCATE = 0x12
      };
      
   // Properties
   public:
      virtual std::string path() = 0;
      virtual std::string path(std::string value) = 0;
      
      virtual FileHandle handle() = 0;
      virtual FileHandle handle(FileHandle value) = 0;
      
      virtual uint32_t flags() = 0;
      virtual uint32_t flags(uint32_t value) = 0;
      
      virtual FileStats stats() = 0;
      virtual FileStats stats(FileStats value) = 0;
      
      virtual uint8_t * data() = 0;
      virtual uint8_t * data(uint8_t * value) = 0;
      
      virtual size_t offset() = 0;
      virtual size_t offset(size_t value) = 0;
      
      virtual size_t length() = 0;
      virtual size_t length(size_t value) = 0;
   };
   
   
   class AsyncIOEvent : public flair::events::Event
   {
      friend class flair::allocator;
      
   protected:
      AsyncIOEvent(const char * type, std::shared_ptr<IAsyncIORequest> request) : flair::events::Event(type, false, false), _request(request) {};
      
   public:
      virtual ~AsyncIOEvent() {};
      
   public:
      std::shared_ptr<IAsyncIORequest> request() { return _request; };
      
   private:
      std::shared_ptr<IAsyncIORequest> _request;
   };
   
   
   class IAsyncIOService : public flair::events::IEventDispatcher
   {
   // Methods
   public:
      virtual void enqueue(std::shared_ptr<IAsyncIORequest> request) = 0;
      
      virtual void poll() = 0;
   };

}}}

#endif
