#include "flair/internal/services/sdl/RenderService.h"
#include "flair/internal/services/sdl/WindowService.h"


namespace flair {
namespace internal {
namespace services {
namespace sdl {
   
   RenderService::RenderService() :
      _renderer(nullptr)
   {
      
   }
   
   RenderService::~RenderService()
   {
      if (_renderer) SDL_DestroyRenderer(_renderer);
   }
   
   SDL_Renderer * RenderService::renderer()
   {
      return _renderer;
   }
   
   void RenderService::create(IWindowService * windowService, bool vsync)
   {
      uint32_t sdlFlags = SDL_RENDERER_ACCELERATED;
      if (vsync) sdlFlags |= SDL_RENDERER_PRESENTVSYNC;
      
      SDL_Window * window = static_cast<WindowService*>(windowService)->window();
      
      _renderer = SDL_CreateRenderer(window, 0, sdlFlags);
   }
   
   void RenderService::clear()
   {
      SDL_RenderClear(_renderer);
   }
   
   void RenderService::present()
   {
      SDL_RenderPresent(_renderer);
   }

}}}}
