#include "flair/ui/Keyboard.h"
#include "flair/internal/services/IKeyboardService.h"

#include <cassert>

namespace flair {
  namespace ui {
     
     flair::internal::services::IKeyboardService * Keyboard::keyboardService = nullptr;
     
     bool Keyboard::capsLock()
     {
        assert(keyboardService);
        return keyboardService->capsLock();
     }
     
     bool Keyboard::hasVirtualKeyboard()
     {
        // TODO: Mobile Virtual Keyboards
        return false;
     }
     
     bool Keyboard::numLock()
     {
        assert(keyboardService);
        return keyboardService->numLock();
     }
     
     KeyboardType Keyboard::physicalKeyboardType()
     {
        // TODO: Keyboard type?
        return KeyboardType::ALPHANUMERIC;
     }
    
  }
}
