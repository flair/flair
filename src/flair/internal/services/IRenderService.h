#ifndef flair_internal_services_IRenderService_h
#define flair_internal_services_IRenderService_h

#include "flair/internal/services/IWindowService.h"
#include "flair/internal/rendering/ITexture.h"
#include "flair/geom/Rectangle.h"
#include "flair/geom/Matrix.h"

namespace flair {
namespace internal {
namespace services {
         
   class IRenderService
   {
   // Properties
   public:
      
   // Methods
   public:
      virtual void create(IWindowService * window, bool vsync = true) = 0;
      
      virtual void clear() = 0;
      
      virtual void present() = 0;
      
      virtual rendering::ITexture * createTexture(int width, int height, rendering::ITexture::PixelFormat format, rendering::ITexture::Type type) = 0;
      
      virtual void renderTexture(rendering::ITexture * texture, geom::Rectangle srcRect, geom::Rectangle dstRect) = 0;
      
      virtual void renderTexture(rendering::ITexture * texture, geom::Rectangle srcRect, geom::Matrix transform) = 0;
      
      virtual void destroyTexture(rendering::ITexture * texture) = 0;
   };
   
}}}

#endif
