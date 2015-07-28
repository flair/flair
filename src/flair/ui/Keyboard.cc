#include "flair/ui/Keyboard.h"
#include "flair/internal/services/Service.h"

extern flair::internal::services::Service ServiceProvider;

namespace flair {
  namespace ui {
     
     bool Keyboard::capsLock()
     {
        return ServiceProvider.keyboardService->capsLock();
     }
     
     bool Keyboard::hasVirtualKeyboard()
     {
        // TODO: Mobile Virtual Keyboards
        return false;
     }
     
     bool Keyboard::numLock()
     {
        return ServiceProvider.keyboardService->numLock();
     }
     
     KeyboardType Keyboard::physicalKeyboardType()
     {
        // TODO: Keyboard type?
        return KeyboardType::ALPHANUMERIC;
     }
    
  }
}
