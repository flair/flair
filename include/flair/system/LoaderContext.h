#ifndef flair_system_LoaderContext_h
#define flair_system_LoaderContext_h

#include "flair/flair.h"
#include "flair/Object.h"
#include "flair/utils/ByteArray.h"

namespace flair { namespace display { class Loader; } }

namespace flair {
namespace system {

   class LoaderContext : public Object
   {
      friend class flair::allocator;
      friend class flair::display::Loader;
      
   protected:
      LoaderContext();
      
   public:
      virtual ~LoaderContext();
      
   // Internal
   protected:
      virtual void decode(std::shared_ptr<utils::ByteArray> bytes, std::function<void(std::shared_ptr<utils::ByteArray>)> callback);
   };

}}

#endif
