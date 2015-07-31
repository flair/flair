#include "flair/desktop/NativeApplication.h"
#include "flair/ui/Keyboard.h"
#include "flair/events/Event.h"
#include "flair/events/KeyboardEvent.h"
#include "flair/internal/EventLoop.h"
#include "flair/internal/services/IWindowService.h"
#include "flair/internal/services/IRenderService.h"
#include "flair/internal/services/IKeyboardService.h"
#include "flair/internal/services/IMouseService.h"
#include "flair/internal/services/ITouchService.h"
#include "flair/internal/services/IGamepadService.h"

#ifdef FLAIR_PLATFORM_SDL
#include "flair/internal/services/sdl/WindowService.h"
#include "flair/internal/services/sdl/RenderService.h"
#include "flair/internal/services/sdl/KeyboardService.h"
#endif

#include <chrono>

namespace flair {
namespace desktop {
   
   using namespace flair::internal;
   using namespace flair::internal::services;
   using namespace flair::display;
   using namespace flair::events;
   
   NativeApplication::NativeApplication(flair::JSON applicationDescriptor, std::shared_ptr<flair::display::Stage> stage) : _applicationDescriptor(applicationDescriptor), _stage(stage), _autoExit(true), _executeInBackground(false), _idleThreshold(300), _systemIdleMode(SystemIdleMode::NORMAL), _running(false)
   {
      windowService = nullptr;
      renderService = nullptr;
      keyboardService = nullptr;
      mouseService = nullptr;
      touchService = nullptr;
      gamepadService = nullptr;
      
#ifdef FLAIR_PLATFORM_SDL
      windowService = new sdl::WindowService();
      keyboardService = new sdl::KeyboardService();
#endif
      
#ifdef FLAIR_RENDERER_SDL
      renderService = new sdl::RenderService();
#endif
      
      eventLoop = new EventLoop();
      ui::Keyboard::keyboardService = keyboardService;
   }
   
   NativeApplication::~NativeApplication()
   {
      delete eventLoop;
   }
   
   std::string NativeApplication::applicationDescriptor()
   {
      // TODO: Return JSON descriptor
      return "";
   }
   
   std::string NativeApplication::applicationID()
   {
      // TODO: Return application ID
      return "";
   }
   
   bool NativeApplication::autoExit()
   {
      return _autoExit;
   }
   
   bool NativeApplication::autoExit(bool value)
   {
      return _autoExit = value;
   }
   
   bool NativeApplication::executeInBackground()
   {
      return _executeInBackground;
   }
   
   bool NativeApplication::executeInBackground(bool value)
   {
      return _executeInBackground = value;
   }
   
   int NativeApplication::idleThreshold()
   {
      return _idleThreshold;
   }
   
   int NativeApplication::idleThreshold(int value)
   {
      return _idleThreshold = value;
   }
   
   std::string NativeApplication::publisherID()
   {
      // TODO: Return publisher ID
      return "";
   }
   
   uint32_t NativeApplication::runtimePatchLevel()
   {
      // TODO: Return runtime patch level
      return 0;
   }
   
   uint32_t NativeApplication::runtimeVersion()
   {
      // TODO: Return runtime version
      return 0;
   }
   
   bool NativeApplication::supportsMenu()
   {
      // TODO: Determine if menu is supported on this platform
      return false;
   }
   
   SystemIdleMode NativeApplication::systemIdleMode()
   {
      return _systemIdleMode;
   }
   
   SystemIdleMode NativeApplication::systemIdleMode(SystemIdleMode value)
   {
      return _systemIdleMode = value;
   }
   
   int NativeApplication::timeSinceLastUserInput()
   {
      // TODO: Return time since last update in seconds
      return 0;
   }
   
   void NativeApplication::activate(int * window)
   {
      // TODO: Activate the window
   }
   
   void NativeApplication::clear()
   {
      // TODO: Send clear command to active element
   }
   
   void NativeApplication::copy()
   {
      // TODO: Send copy command to active element
   }
   
   void NativeApplication::cut()
   {
      // TODO: Send cut command to active element
   }
   
   void NativeApplication::exit(int errorCode)
   {
      // TODO: Send exit command to active element
   }
   
   void NativeApplication::paste()
   {
      // TODO: Send paste command to active element
   }
   
   void NativeApplication::selectAll()
   {
      // TODO: Send selectAll command to active element
   }
   
   void NativeApplication::run()
   {
      if (_running) return;
      _running = true;
      
      JSON initialWindow = _applicationDescriptor["initialWindow"];
      
      uint32_t flags = 0;
      if (initialWindow["requestedDisplayResolution"].isString() && initialWindow["requestedDisplayResolution"].string_value() == "high") flags |= WindowServiceFlags::HIGH_DPI;
      if (initialWindow["fullscreen"].isBool() && initialWindow["fullscreen"].bool_value()) flags |= WindowServiceFlags::FULLSCREEN;
      if (initialWindow["minimizable"].isBool() && initialWindow["minimizable"].bool_value()) flags |= WindowServiceFlags::MINIMIZABLE;
      if (initialWindow["maximizable"].isBool() && initialWindow["maximizable"].bool_value()) flags |= WindowServiceFlags::MAXIMIZEABLE;
      if (initialWindow["resizeable"].isBool() && initialWindow["resizeable"].bool_value()) flags |= WindowServiceFlags::RESIZEABLE;
      
      int width = 320, height = 240, x = -1, y = -1;
      if (initialWindow["width"].isNumber()) width = initialWindow["width"].number_value();
      if (initialWindow["height"].isNumber()) height = initialWindow["height"].number_value();
      if (initialWindow["x"].isNumber()) x = initialWindow["x"].number_value();
      if (initialWindow["y"].isNumber()) y = initialWindow["y"].number_value();
      
      std::string title = "flair";
      if (initialWindow["title"].isString()) title = initialWindow["title"].string_value();
      
      windowService->create(title, geom::Rectangle(x, y, width, height), flags, true);
      renderService->create(windowService, true);
      
      windowService->activate();
      _stage->dispatchEvent(flair::make_shared<Event>(Event::ACTIVATE, false, false));
      
      auto previousTime = std::chrono::high_resolution_clock::now();
      while (!windowService->quiting()) {
         windowService->pollEvents(gamepadService, touchService, mouseService, keyboardService);
         
         // Dispatch keyboard events
         {
            int shift = 0, alt = 0, ctrl = 0, os = 0;
            keyboardService->modifiers(&shift, &alt, &ctrl, &os);
            keyboardService->activeKeys([&](uint32_t keyCode, int keyState) {
               _stage->dispatchEvent(flair::make_shared<KeyboardEvent>(keyState < 0 ? KeyboardEvent::KEY_DOWN : KeyboardEvent::KEY_UP, true, false, keyCode, keyCode, 0, ctrl != 0, alt != 0, shift != 0, ctrl !=0 || os != 0, os != 0));
            });
         }
         
         auto currentTime = std::chrono::high_resolution_clock::now();
         auto deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - previousTime).count();
         previousTime = std::chrono::high_resolution_clock::now();
         _stage->tick(deltaTime / 1000.0f);
         
         renderService->clear();
         renderService->present();
      }
      
      _stage->dispatchEvent(flair::make_shared<Event>(Event::DEACTIVATE, false, false));
      
#ifdef FLAIR_PLATFORM_SDL
      delete static_cast<sdl::WindowService*>(windowService); windowService = nullptr;
      delete static_cast<sdl::KeyboardService*>(keyboardService); keyboardService = nullptr;
#endif
      
#ifdef FLAIR_RENDERER_SDL
      delete static_cast<sdl::RenderService*>(renderService); renderService = nullptr;
#endif
   }
      
}}
