#ifndef flair_internal_services_sdl_RenderService_h
#define flair_internal_services_sdl_RenderService_h

#include "flair/internal/services/IRenderService.h"

#include "SDL.h"

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
      
   // Internal
   private:
      SDL_Renderer * _renderer;
      
   };
   
}}}}

#endif
