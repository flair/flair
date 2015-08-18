#ifndef flair_internal_services_sdl_RenderService_h
#define flair_internal_services_sdl_RenderService_h

#include "flair/internal/services/IRenderService.h"
#include "flair/internal/rendering/ITexture.h"

#include "SDL.h"
#undef ERROR

namespace flair {
namespace internal {
namespace services {
namespace sdl {
   
   class RenderService : public IRenderService
   {
   public:
      RenderService();
      virtual ~RenderService();
      
   // Properties
   public:
      SDL_Renderer * renderer();
      
   // Methods
   public:
      void create(IWindowService * windowService, bool vsync = true) override;
      
      void clear() override;
      
      void present() override;
      
      rendering::ITexture * createTexture(int width, int height, rendering::ITexture::PixelFormat format, rendering::ITexture::Type type) override;
      
      void renderTexture(rendering::ITexture * texture, geom::Rectangle srcRect, geom::Rectangle dstRect) override;
      
      void renderTexture(rendering::ITexture * texture, geom::Rectangle srcRect, geom::Matrix transform) override;
      
      void destroyTexture(rendering::ITexture * texture) override;
      
   // Internal
   private:
      SDL_Renderer * _renderer;
      
   };
   
}}}}

#endif
