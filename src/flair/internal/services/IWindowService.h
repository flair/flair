#ifndef flair_internal_services_IWindowService_h
#define flair_internal_services_IWindowService_h

#include "flair/internal/services/IGamepadService.h"
#include "flair/internal/services/ITouchService.h"
#include "flair/internal/services/IKeyboardService.h"
#include "flair/internal/services/IMouseService.h"

#include "flair/geom/Rectangle.h"

#include <string>
#include <cstdint>

namespace flair {
   namespace internal {
      namespace services {
         
         struct WindowServiceFlags
         {
            enum {
               FULLSCREEN = 0x01,
               HIGH_DPI = 0x02,
               RESIZEABLE = 0x04,
               MINIMIZABLE = 0x08,
               MAXIMIZEABLE = 0x10,
               MOUSE_CAPTURE = 0x12
            };
         };
         
         class IWindowService
         {
         // Properties
         public:
            virtual bool rootWindow() = 0;
            
            virtual flair::geom::Rectangle bounds() = 0;
            virtual flair::geom::Rectangle bounds(flair::geom::Rectangle const& value) = 0;
            
            virtual bool active() = 0;
            virtual bool closing() = 0;
            virtual bool quiting() = 0;
            
            virtual bool minimzed() = 0;
            virtual bool maximized() = 0;
            
            virtual bool fullscreen() = 0;
            
            
         // Methods
         public:
            virtual void create(std::string title, flair::geom::Rectangle const& bounds, uint32_t flags = 0, bool root = false) = 0;
            
            virtual void activate() = 0;
            virtual void close() = 0;
            
            virtual void minimize() = 0;
            virtual void maximize() = 0;
            virtual void restore() = 0;
            
            virtual bool enterFullscreen(int width, int height, bool useClosestResolution = true) = 0;
            virtual void exitFullscreen() = 0;
            
            virtual void pollEvents(IGamepadService * gamepadService, ITouchService * touchService, IMouseService * mouseService, IKeyboardService * keyboardService) = 0;
         };
         
      }
   }
}

#endif
