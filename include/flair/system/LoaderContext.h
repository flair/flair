#ifndef flair_system_LoaderContext_h
#define flair_system_LoaderContext_h

#include "flair/flair.h"
#include "flair/Object.h"
#include "flair/utils/ByteArray.h"
#include "flair/display/DisplayObject.h"

namespace flair { namespace display { class Loader; } }
namespace flair { namespace desktop { class NativeApplication; } }
namespace flair { namespace internal { namespace services { class IWorkerService; } } }

namespace flair {
namespace system {

   class LoaderContext : public Object
   {
      friend class flair::allocator;
      
   protected:
      LoaderContext();
      
   public:
      virtual ~LoaderContext();
      
   // Internal
   protected:
      friend class flair::display::Loader;
      virtual void decode(std::shared_ptr<utils::ByteArray> bytes, std::function<void(std::shared_ptr<utils::ByteArray>)> callback);
      virtual void create(std::shared_ptr<utils::ByteArray> bytes, std::function<void(std::shared_ptr<display::DisplayObject>)> callback);
      
      friend class flair::desktop::NativeApplication;
      static flair::internal::services::IWorkerService * workerService;
   };

}}

#endif
