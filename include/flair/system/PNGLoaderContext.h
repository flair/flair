#ifndef flair_system_PNGLoaderContext_h
#define flair_system_PNGLoaderContext_h

#include "flair/flair.h"
#include "flair/system/LoaderContext.h"

namespace flair { namespace display { class Loader; } }

namespace flair {
namespace system {
   
   class PNGLoaderContext : public LoaderContext
   {
      friend class flair::allocator;
      friend class flair::display::Loader;
      
   protected:
      PNGLoaderContext();
      
   public:
      virtual ~PNGLoaderContext();
      
   // Internal
   protected:
      void decode(std::shared_ptr<utils::ByteArray> bytes, std::function<void(std::shared_ptr<utils::ByteArray>)> callback) override;
   };
   
}}

#endif
