#include "flair/desktop/NativeApplication.h"
#include "flair/ui/Keyboard.h"
#include "flair/events/Event.h"
#include "flair/events/KeyboardEvent.h"
#include "flair/events/MouseEvent.h"
#include "flair/net/FileReference.h"
#include "flair/net/URLRequest.h"
#include "flair/display/BitmapData.h"
#include "flair/system/LoaderContext.h"
#include "flair/display/RenderSupport.h"
#include "flair/internal/services/IWindowService.h"
#include "flair/internal/services/IRenderService.h"
#include "flair/internal/services/IKeyboardService.h"
#include "flair/internal/services/IMouseService.h"
#include "flair/internal/services/ITouchService.h"
#include "flair/internal/services/IGamepadService.h"
#include "flair/internal/services/IAsyncIOService.h"
#include "flair/internal/services/IFileService.h"
#include "flair/internal/services/IPlatformService.h"

#ifdef FLAIR_PLATFORM_SDL
#include "flair/internal/services/sdl/WindowService.h"
#include "flair/internal/services/sdl/RenderService.h"
#include "flair/internal/services/sdl/KeyboardService.h"
#include "flair/internal/services/sdl/MouseService.h"
#endif

#ifdef FLAIR_IO_UV
#include "flair/internal/services/uv/AsyncIOService.h"
#include "flair/internal/services/uv/FileService.h"
#include "flair/internal/services/uv/WorkerService.h"
#endif

#ifdef FLAIR_PLATFORM_MAC
#include "flair/internal/services/mac/PlatformService.h"
#endif

#ifdef FLAIR_PLATFORM_WINDOWS
#include "flair/internal/services/windows/PlatformService.h"
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
      platformService = nullptr;
      asyncIOService = nullptr;
      fileService = nullptr;
      workerService = nullptr;
      
#ifdef FLAIR_PLATFORM_SDL
      windowService = new sdl::WindowService();
      keyboardService = new sdl::KeyboardService();
      mouseService = new sdl::MouseService();
#endif
      
#ifdef FLAIR_RENDERER_SDL
      renderService = new sdl::RenderService();
#endif
      
#ifdef FLAIR_IO_UV
      asyncIOService = new uv::AsyncIOService();
      fileService = new uv::FileService();
      workerService = new uv::WorkerService();
#endif
      
#ifdef FLAIR_PLATFORM_MAC
      platformService = new mac::PlatformService();
#endif

#ifdef FLAIR_PLATFORM_WINDOWS
      platformService = new windows::PlatformService();
#endif
      
      // Setup dependency services
      fileService->init(asyncIOService);
      workerService->init(asyncIOService);
      
      // Inject services into the public api
      ui::Keyboard::keyboardService = keyboardService;
      net::FileReference::fileService = fileService;
      net::FileReference::platformService = platformService;
      net::URLRequest::platformService = platformService;
      display::BitmapData::renderService = renderService;
      display::RenderSupport::renderService = renderService;
      system::LoaderContext::workerService = workerService;
   }
   
   NativeApplication::~NativeApplication()
   {
#ifdef FLAIR_PLATFORM_SDL
      delete static_cast<sdl::WindowService*>(windowService);
      delete static_cast<sdl::KeyboardService*>(keyboardService);
      delete static_cast<sdl::MouseService*>(mouseService);
#endif
      
#ifdef FLAIR_RENDERER_SDL
      delete static_cast<sdl::RenderService*>(renderService);
#endif
      
#ifdef FLAIR_IO_UV
      delete static_cast<uv::AsyncIOService*>(asyncIOService);
      delete static_cast<uv::FileService*>(fileService);
      delete static_cast<uv::WorkerService*>(workerService);
#endif
      
#ifdef FLAIR_PLATFORM_MAC
      delete static_cast<mac::PlatformService*>(platformService);
#endif

#ifdef FLAIR_PLATFORM_WINDOWS
      delete static_cast<windows::PlatformService*>(platformService);
#endif
   }
   
   flair::JSON NativeApplication::applicationDescriptor()
   {
      return _applicationDescriptor;
   }
   
   std::string NativeApplication::applicationID()
   {
      return _applicationDescriptor["id"].isString() ? _applicationDescriptor["id"].string_value() : "";
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
      windowService->close();
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
      
      bool vsync = false;
      if (initialWindow["vsync"].isBool()) vsync = initialWindow["vsync"].bool_value();
      
      auto renderSupport = new RenderSupport();
      
      windowService->create(title, geom::Rectangle(x, y, width, height), flags, true);
      renderService->create(windowService, vsync);
      
      windowService->activate();
      _stage->_stageWidth = width;
      _stage->_stageHeight = height;
      _stage->dispatchEvent(flair::make_shared<Event>(Event::ACTIVATE, false, false));
      
      auto previousTime = std::chrono::high_resolution_clock::now();
      while (!windowService->quiting()) {
         asyncIOService->poll();
         windowService->poll(gamepadService, touchService, mouseService, keyboardService);
         
         // Dispatch keyboard events
         {
            int shift = 0, alt = 0, ctrl = 0, os = 0;
            keyboardService->modifiers(&shift, &alt, &ctrl, &os);
            keyboardService->activeKeys([&](uint32_t keyCode, int keyState) {
               _stage->dispatchEvent(flair::make_shared<KeyboardEvent>(keyState < 0 ? KeyboardEvent::KEY_DOWN : KeyboardEvent::KEY_UP, true, false, keyCode, keyCode, 0, ctrl != 0, alt != 0, shift != 0, ctrl !=0 || os != 0, os != 0));
            });
         }
         
         // Dispatch mouse events
         {
            int shift = 0, alt = 0, ctrl = 0, os = 0;
            bool primaryButtonDown = false;
            keyboardService->modifiers(&shift, &alt, &ctrl, &os);
            mouseService->buttonStates([&](uint32_t buttonCode, int currentState, int prevState) {
               const char * mouseEventType = nullptr;
               
               int localX, localY, movementX, movementY;
               mouseService->location(&localX, &localY);
               mouseService->movement(&movementX, &movementY);
               
               
               // Button Up / Down Events
               mouseEventType = nullptr;
               if (currentState < 0) {
                  if (buttonCode == IMouseService::MIDDLE_BUTTON) {
                     mouseEventType = MouseEvent::MIDDLE_MOUSE_DOWN;
                  }
                  else if (buttonCode == IMouseService::RIGHT_BUTTON) {
                     mouseEventType = MouseEvent::RIGHT_MOUSE_DOWN;
                  }
                  else {
                     mouseEventType = MouseEvent::MOUSE_DOWN;
                     primaryButtonDown = true;
                  }
               }
               else if (currentState > 0) {
                  if (buttonCode == IMouseService::MIDDLE_BUTTON) {
                     mouseEventType = MouseEvent::MIDDLE_MOUSE_UP;
                  }
                  else if (buttonCode == IMouseService::RIGHT_BUTTON) {
                     mouseEventType = MouseEvent::RIGHT_MOUSE_UP;
                  }
                  else {
                     mouseEventType = MouseEvent::MOUSE_UP;
                  }
               }
               
               if (mouseEventType) {
                  _stage->dispatchEvent(flair::make_shared<MouseEvent>(mouseEventType, true, false, (float)localX, (float)localY, (float)movementX, (float)movementY, nullptr, primaryButtonDown, 0, std::abs(currentState), ctrl != 0, alt != 0, shift != 0, ctrl !=0 || os != 0, os != 0));
               }
               
               
               // Click / Double Click Events
               mouseEventType = nullptr;
               if (prevState >= 0 && currentState < 0) {
                  if (buttonCode == IMouseService::MIDDLE_BUTTON) {
                     mouseEventType = MouseEvent::MIDDLE_CLICK;
                  }
                  else if (buttonCode == IMouseService::RIGHT_BUTTON) {
                     mouseEventType = MouseEvent::RIGHT_CLICK;
                  }
                  else {
                     mouseEventType = (currentState == -2 ? MouseEvent::DOUBLE_CLICK : MouseEvent::CLICK);
                  }
               }
               
               if (mouseEventType) {
                  _stage->dispatchEvent(flair::make_shared<MouseEvent>(mouseEventType, true, false, (float)localX, (float)localY, (float)movementX, (float)movementY, nullptr, primaryButtonDown, 0, std::abs(currentState), ctrl != 0, alt != 0, shift != 0, ctrl !=0 || os != 0, os != 0));
               }
               
               
               // Movement Events
               if (movementX != 0 || movementY != 0) {
                  _stage->dispatchEvent(flair::make_shared<MouseEvent>(MouseEvent::MOUSE_MOVE, true, false, (float)localX, (float)localY, (float)movementX, (float)movementY, nullptr, primaryButtonDown, 0, std::abs(currentState), ctrl != 0, alt != 0, shift != 0, ctrl !=0 || os != 0, os != 0));
               }
            });
         }
         
         auto currentTime = std::chrono::high_resolution_clock::now();
         auto deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - previousTime).count();
         previousTime = std::chrono::high_resolution_clock::now();
         _stage->tick(deltaTime / 1000.0f);
         
         renderService->clear();
         _stage->render(renderSupport, _stage->alpha(), geom::Matrix());
         renderService->present();
      }
      
      _stage->dispatchEvent(flair::make_shared<Event>(Event::DEACTIVATE, false, false));
      
      delete renderSupport;
   }
      
}}
