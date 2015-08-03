#ifndef flair_internal_services_sdl_WindowService_h
#define flair_internal_services_sdl_WindowService_h

#include "flair/internal/services/IWindowService.h"

#include "SDL.h"

#include <string>

namespace flair {
namespace internal {
namespace services {
namespace sdl {
   
   class WindowService : public IWindowService
   {
   public:
      WindowService();
      virtual ~WindowService();
      
   // Properties
   public:
      bool rootWindow() override;
      
      flair::geom::Rectangle bounds() override;
      flair::geom::Rectangle bounds(flair::geom::Rectangle const& value) override;
      
      bool active() override;
      bool closing() override;
      bool quiting() override;
      
      bool minimzed() override;
      bool maximized() override;
      
      bool fullscreen() override;
      
      SDL_Window * window();
      
      
   // Methods
   public:
      void create(std::string title, flair::geom::Rectangle const& bounds, uint32_t flags = 0, bool root = false) override;
      
      void activate() override;
      void close() override;
      
      void minimize() override;
      void maximize() override;
      void restore() override;
      
      bool enterFullscreen(int width, int height, bool useClosestResolution = true) override;
      void exitFullscreen() override;
      
      void poll(IGamepadService * gamepadService, ITouchService * touchService, IMouseService * mouseService, IKeyboardService * keyboardService) override;
      
   // Internal
   private:
      bool _rootWindow;
      
      flair::geom::Rectangle _bounds;
      
      bool _active;
      bool _closing;
      bool _quiting;
      
      bool _minimized;
      bool _maximized;
      bool _fullscreen;
      
      SDL_Window * _window;
   };
   
}}}}

#endif
