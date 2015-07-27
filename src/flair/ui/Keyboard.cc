#include "flair/ui/Keyboard.h"
#include "flair/internal/services/Service.h"

extern flair::internal::services::Service ServiceProvider;

namespace flair {
  namespace ui {
     
     bool Keyboard::capsLock()
     {
        ServiceProvider.keyboardService;
     }
     
     bool Keyboard::hasVirtualKeyboard()
     {
        ServiceProvider.keyboardService;
     }
     
     bool Keyboard::numLock()
     {
        ServiceProvider.keyboardService;
     }
     
     int Keyboard::physicalKeyboardType()
     {
        ServiceProvider.keyboardService;
     }
    
  }
}
