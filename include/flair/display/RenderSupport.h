#ifndef flair_display_RenderSupport_h
#define flair_display_RenderSupport_h

#include "flair/flair.h"
#include "flair/geom/Matrix.h"

namespace flair { namespace desktop { class NativeApplication; } }
namespace flair { namespace internal { namespace services { class IRenderService; } } }
namespace flair { namespace display { class Bitmap; } }

namespace flair {
namespace display {
      
      class RenderSupport
      {
         friend class flair::desktop::NativeApplication;
         
      protected:
         RenderSupport();
         
      public:
         virtual ~RenderSupport();
         
         
      // Methods
      public:
         void renderBitmap(std::shared_ptr<Bitmap> bitmap, geom::Matrix transform);
         
         
      // Internal
      protected:
         static flair::internal::services::IRenderService * renderService;
      };
      
}}

#endif
