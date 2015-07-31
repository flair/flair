#include "flair/flair.h"
#include "flair/desktop/NativeApplication.h"
#include "flair/display/Stage.h"
#include "flair/events/Event.h"
#include "flair/events/KeyboardEvent.h"
#include "flair/geom/Rectangle.h"
#include "flair/internal/services/IWindowService.h"
#include "flair/internal/services/IRenderService.h"
#include "flair/internal/services/IKeyboardService.h"

#ifdef FLAIR_PLATFORM_SDL
#include "flair/internal/services/sdl/WindowService.h"
#include "flair/internal/services/sdl/RenderService.h"
#include "flair/internal/services/sdl/KeyboardService.h"
#endif

#include <chrono>

namespace flair {
   using flair::desktop::NativeApplication;
   
   void run(flair::JSON const& applicationDescriptor, std::shared_ptr<flair::display::Stage> stage)
   {
      auto nativeApp = NativeApplication::nativeApplication(applicationDescriptor, stage);
      nativeApp->run();
   }
   
}
