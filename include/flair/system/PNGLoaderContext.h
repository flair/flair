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
      
   protected:
      PNGLoaderContext();
      
   public:
      virtual ~PNGLoaderContext();
      
   // Internal
   protected:
      friend class flair::display::Loader;
      void decode(std::shared_ptr<utils::ByteArray> bytes, std::function<void(std::shared_ptr<utils::ByteArray>)> callback) override;
      void create(std::shared_ptr<utils::ByteArray> bytes, std::function<void(std::shared_ptr<display::DisplayObject>)> callback) override;
   };
   
}}

#endif
