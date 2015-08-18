#include "flair/display/RenderSupport.h"
#include "flair/geom/Rectangle.h"
#include "flair/display/Bitmap.h"
#include "flair/internal/services/IRenderService.h"

#include <cmath>

namespace flair {
namespace display {
   
   flair::internal::services::IRenderService * RenderSupport::renderService = nullptr;
   
   RenderSupport::RenderSupport()
   {
      
   }
   
   RenderSupport::~RenderSupport()
   {
      
   }
   
   void RenderSupport::renderBitmap(std::shared_ptr<Bitmap> bitmap, geom::Matrix transform)
   {      
      geom::Rectangle src(0, 0, bitmap->width(), bitmap->height());
      renderService->renderTexture(bitmap->bitmapData()->texture, src, transform);
   }
   
}}
