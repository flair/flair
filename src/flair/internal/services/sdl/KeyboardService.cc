#include "flair/internal/services/sdl/KeyboardService.h"

namespace flair {
namespace internal {
namespace services {
namespace sdl {
   
   void KeyboardService::modifiers(int shift, int alt, int ctrl, int os)
   {
      _modifiers.shift = (shift < 0 ? -1 : shift > 0 ? 1 : 0);
      _modifiers.alt = (alt < 0 ? -1 : alt > 0 ? 1 : 0);
      _modifiers.ctrl = (ctrl < 0 ? -1 : ctrl > 0 ? 1 : 0);
      _modifiers.os = (os < 0 ? -1 : os > 0 ? 1 : 0);
   }
   
   void KeyboardService::modifiers(int * shift, int * alt, int * ctrl, int * os)
   {
      *shift = _modifiers.shift;
      *alt = _modifiers.alt;
      *ctrl = _modifiers.ctrl;
      *os = _modifiers.os;
   }
   
   void KeyboardService::key(uint32_t keyCode, int state)
   {
      if (keyCode >= flair::ui::Keyboard::_KEY_COUNT) return;
      _keys[keyCode] = state;
   }
   
   void KeyboardService::key(uint32_t keyCode, int * state)
   {
      if (keyCode >= flair::ui::Keyboard::_KEY_COUNT) return;
      *state = _keys[keyCode];
   }
   
   void KeyboardService::activeKeys(std::function<void(uint32_t keyCode, int keyState)> callback)
   {
      for (uint32_t i = 0; i < flair::ui::Keyboard::_KEY_COUNT; ++i )
      {
         if (_keys[i] != 0) callback(i, _keys[i]);
      }
   }
   
   void KeyboardService::clear()
   {
      memset(_keys, 0, sizeof(_keys));
      memset(&_modifiers, 9, sizeof(_modifiers));
   }
   
}}}}
