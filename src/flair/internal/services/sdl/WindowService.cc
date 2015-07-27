#include "flair/internal/services/sdl/WindowService.h"

namespace flair {
namespace internal {
namespace services {
namespace sdl {
   
   WindowService::WindowService() :
      _rootWindow(false), _active(false), _closing(false), _quiting(false),
      _minimized(false), _maximized(false), _fullscreen(false), _window(nullptr)
   {
      static bool initialized = false;
      if (!initialized) {
         SDL_Init(SDL_INIT_EVERYTHING);
         initialized = true;
      }
   }
   
   WindowService::~WindowService()
   {
      if (_rootWindow) SDL_Quit();
   }
   
   bool WindowService::rootWindow()
   {
      return _rootWindow;
   }
   
   geom::Rectangle WindowService::bounds()
   {
      return _bounds;
   }
   
   geom::Rectangle WindowService::bounds(geom::Rectangle const& value)
   {
      return _bounds = value;
   }
   
   bool WindowService::active()
   {
      return _active;
   }
   
   bool WindowService::closing()
   {
      return _closing;
   }
   
   bool WindowService::quiting()
   {
      return _quiting;
   }
   
   bool WindowService::minimzed()
   {
      return _minimized;
   }
   
   bool WindowService::maximized()
   {
      return _maximized;
   }
   
   bool WindowService::fullscreen()
   {
      return _fullscreen;
   }
   
   SDL_Window * WindowService::window()
   {
      return _window;
   }
   
   void WindowService::create(std::string title, flair::geom::Rectangle const& bounds, uint32_t flags, bool root)
   {
      uint32_t sdlFlags = 0;
      if (flags & WindowServiceFlags::FULLSCREEN) sdlFlags |= SDL_WINDOW_FULLSCREEN;
      if (flags & WindowServiceFlags::HIGH_DPI) sdlFlags |= SDL_WINDOW_ALLOW_HIGHDPI;
      if (flags & WindowServiceFlags::MOUSE_CAPTURE) sdlFlags |= SDL_WINDOW_MOUSE_CAPTURE;
      
      int x = bounds.x();
      int y = bounds.y();
      int width = bounds.width();
      int height = bounds.height();
      
      if (x < 0 || y < 0) {
         x = SDL_WINDOWPOS_UNDEFINED;
         y = SDL_WINDOWPOS_UNDEFINED;
      }
      
      if (flags & WindowServiceFlags::FULLSCREEN) {
         SDL_DisplayMode mode;
         if (width <= 0 || height <= 0) {
            SDL_GetCurrentDisplayMode(0, &mode);
         }
         else {
            SDL_DisplayMode closestMode;
            
            mode.w = width;
            mode.h = height;
            mode.format = 0;
            mode.driverdata = nullptr;
            
            if (SDL_GetClosestDisplayMode(0, &mode, &closestMode) != nullptr) {
               mode = closestMode;
            }
            else {
               SDL_GetCurrentDisplayMode(0, &mode);
            }
         }
         
         width = mode.w;
         height = mode.w;
      }
      
      _rootWindow = root;
      _window = SDL_CreateWindow(title.c_str(), x, y, width, height, sdlFlags);
      
      if (_window == nullptr) {
         printf("Could not create window: %s\n", SDL_GetError());
      }
   }
   
   void WindowService::activate()
   {
      if (!_active) return;
      
      _active = true;
      _active = true;
      SDL_ShowWindow(_window);
   }
   
   void WindowService::close()
   {
      if (_closing) return;
      
      _closing = true;
      if (_rootWindow) _quiting = true;
      
      SDL_DestroyWindow(_window);
   }
   
   void WindowService::minimize()
   {
      if (_minimized) return;
      
      SDL_MinimizeWindow(_window);
      _minimized = true;
   }
   
   void WindowService::maximize()
   {
      if (_maximized || _fullscreen) return;
      
      SDL_MaximizeWindow(_window);
      _minimized = false;
      _maximized = true;
   }
   
   void WindowService::restore()
   {
      if (!_minimized || !_maximized) return;
      
      SDL_RestoreWindow(_window);
      _minimized = _maximized = false;
   }
   
   bool WindowService::enterFullscreen(int width, int height, bool useClosestResolution)
   {
      return false;
   }
   
   void WindowService::exitFullscreen()
   {
      
   }
   
   void WindowService::pollEvents(IGamepadService * gamepadService, ITouchService * touchService, IMouseService * mouseService, IKeyboardService * keyboardService)
   {
      if (!_rootWindow) return;
      if (keyboardService) keyboardService->clear();
      
      SDL_Event event;
      while (SDL_PollEvent(&event)) {
         switch (event.type) {
            case SDL_QUIT: {
               _quiting = true;
            } break;
               
            case SDL_KEYDOWN: {
               if (keyboardService) {
                  keyboardService->modifiers(
                     (event.key.keysym.mod & KMOD_LSHIFT) ? -1 : (event.key.keysym.mod & KMOD_RSHIFT) ? 1 : 0,
                     (event.key.keysym.mod & KMOD_LALT) ? -1 : (event.key.keysym.mod & KMOD_RALT) ? 1 : 0,
                     (event.key.keysym.mod & KMOD_LCTRL) ? -1 : (event.key.keysym.mod & KMOD_RCTRL) ? 1 : 0,
                     (event.key.keysym.mod & KMOD_LGUI) ? -1 : (event.key.keysym.mod & KMOD_RGUI) ? 1 : 0
                  );
                  if (!event.key.repeat) keyboardService->key(event.key.keysym.sym, -1);
               }
               
               if (event.key.keysym.sym == SDLK_ESCAPE) {
                  _quiting = true;
               }
            } break;
               
            case SDL_KEYUP: {
               if (keyboardService) {
                  keyboardService->modifiers(
                     (event.key.keysym.mod & KMOD_LSHIFT) ? -1 : (event.key.keysym.mod & KMOD_RSHIFT) ? 1 : 0,
                     (event.key.keysym.mod & KMOD_LALT) ? -1 : (event.key.keysym.mod & KMOD_RALT) ? 1 : 0,
                     (event.key.keysym.mod & KMOD_LCTRL) ? -1 : (event.key.keysym.mod & KMOD_RCTRL) ? 1 : 0,
                     (event.key.keysym.mod & KMOD_LGUI) ? -1 : (event.key.keysym.mod & KMOD_RGUI) ? 1 : 0
                  );
                  keyboardService->key(event.key.keysym.sym, 1);
               }
            } break;
               
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
            case SDL_MOUSEMOTION:
               break;
               
            case SDL_WINDOWEVENT: {
               switch (event.window.event) {
                  case SDL_WINDOWEVENT_SHOWN:
                     break;
                  case SDL_WINDOWEVENT_CLOSE:
                     break;
               }
            } break;
         }
      }
   }
   

}}}}