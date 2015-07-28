#include "flair/flair.h"
#include "flair/desktop/NativeApplication.h"
#include "flair/display/Stage.h"
#include "flair/events/Event.h"
#include "flair/events/KeyboardEvent.h"
#include "flair/geom/Rectangle.h"
#include "flair/internal/services/Service.h"
#include "flair/internal/services/IWindowService.h"
#include "flair/internal/services/IRenderService.h"

#ifdef FLAIR_PLATFORM_SDL
#include "flair/internal/services/sdl/WindowService.h"
#include "flair/internal/services/sdl/KeyboardService.h"
#include "flair/internal/services/sdl/RenderService.h"
#endif

#include <chrono>

flair::internal::services::Service ServiceProvider;


namespace flair {
   using namespace flair::internal::services;
   using flair::desktop::NativeApplication;
   using flair::events::Event;
   using flair::events::KeyboardEvent;
   
   void run(std::shared_ptr<flair::display::Stage> stage, int width, int height, bool fullscreen)
   {
      auto nativeApp = NativeApplication::nativeApplication();
      
      ServiceProvider.windowService = nullptr;
      ServiceProvider.renderService = nullptr;
      ServiceProvider.gamepadService = nullptr;
      ServiceProvider.touchService = nullptr;
      ServiceProvider.mouseService = nullptr;
      ServiceProvider.keyboardService = nullptr;
      ServiceProvider.touchService = nullptr;
      
#ifdef FLAIR_PLATFORM_SDL
      ServiceProvider.windowService = new sdl::WindowService();
      ServiceProvider.keyboardService = new sdl::KeyboardService();
#endif
      
#ifdef FLAIR_RENDERER_SDL
      ServiceProvider.renderService = new sdl::RenderService();
#endif
      
      uint32_t flags = WindowServiceFlags::HIGH_DPI;
      if (fullscreen) flags |= WindowServiceFlags::FULLSCREEN;
      
      ServiceProvider.windowService->create("flair", geom::Rectangle(-1, -1, width, height), flags, true);
      ServiceProvider.renderService->create(ServiceProvider.windowService, true);
      
      ServiceProvider.windowService->activate();
      stage->dispatchEvent(flair::make_shared<Event>(Event::ACTIVATE, false, false));

      auto previousTime = std::chrono::high_resolution_clock::now();
      while (!ServiceProvider.windowService->quiting()) {
         ServiceProvider.windowService->pollEvents(ServiceProvider.gamepadService, ServiceProvider.touchService, ServiceProvider.mouseService, ServiceProvider.keyboardService);
         
         // Dispatch keyboard events
         {
            int shift = 0, alt = 0, ctrl = 0, os = 0;
            ServiceProvider.keyboardService->modifiers(&shift, &alt, &ctrl, &os);
            ServiceProvider.keyboardService->activeKeys([&](uint32_t keyCode, int keyState) {
               stage->dispatchEvent(flair::make_shared<KeyboardEvent>(keyState < 0 ? KeyboardEvent::KEY_DOWN : KeyboardEvent::KEY_UP, true, false, keyCode, keyCode, 0, ctrl != 0, alt != 0, shift != 0, ctrl !=0 || os != 0, os != 0));
            });
         }
         
         auto currentTime = std::chrono::high_resolution_clock::now();
         auto deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - previousTime).count();
         previousTime = std::chrono::high_resolution_clock::now();
         stage->tick(deltaTime / 1000.0f);
         
         ServiceProvider.renderService->clear();
         ServiceProvider.renderService->present();
      }
      
      stage->dispatchEvent(flair::make_shared<Event>(Event::DEACTIVATE, false, false));
      
#ifdef FLAIR_PLATFORM_SDL
      delete static_cast<sdl::WindowService*>(ServiceProvider.windowService);
      delete static_cast<sdl::KeyboardService*>(ServiceProvider.keyboardService);
#endif
      
#ifdef FLAIR_RENDERER_SDL
      delete static_cast<sdl::RenderService*>(ServiceProvider.renderService);
#endif
   }
   
}
