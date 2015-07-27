#include "flair/internal/services/sdl/KeyboardService.h"
#include "flair/ui/Keyboard.h"

#include "SDL_keycode.h"
#include <cstring>

namespace {
   using flair::ui::Keyboard;
   
   uint32_t SDLtoKeyboard(uint32_t rawKey)
   {
      switch (rawKey) {
         case SDLK_BACKSPACE: return Keyboard::BACKSPACE;
         case SDLK_TAB: return Keyboard::TAB;
            
         case SDLK_RETURN: return Keyboard::ENTER;
            
         case SDLK_LGUI: return Keyboard::COMMAND;
         case SDLK_RGUI: return Keyboard::COMMAND;
         case SDLK_LSHIFT: return Keyboard::SHIFT;
         case SDLK_RSHIFT: return Keyboard::SHIFT;
         case SDLK_LCTRL: return Keyboard::CONTROL;
         case SDLK_RCTRL: return Keyboard::CONTROL;
         case SDLK_LALT: return Keyboard::ALTERNATE;
         case SDLK_RALT: return Keyboard::ALTERNATE;
            
         case SDLK_CAPSLOCK: return Keyboard::CAPS_LOCK;
            
         case SDLK_ESCAPE: return Keyboard::ESCAPE;
            
         case SDLK_SPACE: return Keyboard::SPACE;
         case SDLK_PAGEUP: return Keyboard::PAGE_UP;
         case SDLK_PAGEDOWN: return Keyboard::PAGE_DOWN;
         case SDLK_END: return Keyboard::END;
         case SDLK_HOME: return Keyboard::HOME;
         case SDLK_LEFT: return Keyboard::LEFT;
         case SDLK_UP: return Keyboard::UP;
         case SDLK_RIGHT: return Keyboard::RIGHT;
         case SDLK_DOWN: return Keyboard::DOWN;
            
         case SDLK_0: return Keyboard::NUMBER_0;
         case SDLK_1: return Keyboard::NUMBER_1;
         case SDLK_2: return Keyboard::NUMBER_2;
         case SDLK_3: return Keyboard::NUMBER_3;
         case SDLK_4: return Keyboard::NUMBER_4;
         case SDLK_5: return Keyboard::NUMBER_5;
         case SDLK_6: return Keyboard::NUMBER_6;
         case SDLK_7: return Keyboard::NUMBER_7;
         case SDLK_8: return Keyboard::NUMBER_8;
         case SDLK_9: return Keyboard::NUMBER_9;
            
         case SDLK_a: return Keyboard::A;
         case SDLK_b: return Keyboard::B;
         case SDLK_c: return Keyboard::C;
         case SDLK_d: return Keyboard::D;
         case SDLK_e: return Keyboard::E;
         case SDLK_f: return Keyboard::F;
         case SDLK_g: return Keyboard::G;
         case SDLK_h: return Keyboard::H;
         case SDLK_i: return Keyboard::I;
         case SDLK_j: return Keyboard::J;
         case SDLK_k: return Keyboard::K;
         case SDLK_l: return Keyboard::L;
         case SDLK_m: return Keyboard::M;
         case SDLK_n: return Keyboard::N;
         case SDLK_o: return Keyboard::O;
         case SDLK_p: return Keyboard::P;
         case SDLK_q: return Keyboard::Q;
         case SDLK_r: return Keyboard::R;
         case SDLK_s: return Keyboard::S;
         case SDLK_t: return Keyboard::T;
         case SDLK_u: return Keyboard::U;
         case SDLK_v: return Keyboard::V;
         case SDLK_w: return Keyboard::W;
         case SDLK_x: return Keyboard::X;
         case SDLK_y: return Keyboard::Y;
         case SDLK_z: return Keyboard::Z;
            
         case SDLK_F1: return Keyboard::F1;
         case SDLK_F2: return Keyboard::F2;
         case SDLK_F3: return Keyboard::F3;
         case SDLK_F4: return Keyboard::F4;
         case SDLK_F5: return Keyboard::F5;
         case SDLK_F6: return Keyboard::F6;
         case SDLK_F7: return Keyboard::F7;
         case SDLK_F8: return Keyboard::F8;
         case SDLK_F9: return Keyboard::F9;
         case SDLK_F10: return Keyboard::F10;
         case SDLK_F11: return Keyboard::F11;
         case SDLK_F12: return Keyboard::F12;
         case SDLK_F13: return Keyboard::F13;
         case SDLK_F14: return Keyboard::F14;
         case SDLK_F15: return Keyboard::F15;
            
         case SDLK_SEMICOLON: return Keyboard::SEMICOLON;
         case SDLK_EQUALS: return Keyboard::EQUAL;
         case SDLK_COMMA: return Keyboard::COMMA;
         case SDLK_MINUS: return Keyboard::MINUS;
         case SDLK_PERIOD: return Keyboard::PERIOD;
         case SDLK_SLASH: return Keyboard::SLASH;
         case SDLK_BACKQUOTE: return Keyboard::BACKQUOTE;
            
         case SDLK_LEFTBRACKET: return Keyboard::LEFTBRACKET;
         case SDLK_BACKSLASH: return Keyboard::BACKSLASH;
         case SDLK_RIGHTBRACKET: return Keyboard::RIGHTBRACKET;
         case SDLK_QUOTE: return Keyboard::QUOTE;
      }
      
      return rawKey;
   }
}

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
      keyCode = SDLtoKeyboard(keyCode);
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
