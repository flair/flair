#include "flair/internal/services/sdl/MouseService.h"

#include "SDL_mouse.h"

namespace {
   using flair::internal::services::IMouseService;
   
   uint32_t SDLtoMouse(uint32_t rawButton)
   {
      switch (rawButton) {
         case SDL_BUTTON_LEFT: return IMouseService::LEFT_BUTTON;
         case SDL_BUTTON_MIDDLE: return IMouseService::MIDDLE_BUTTON;
         case SDL_BUTTON_RIGHT: return IMouseService::RIGHT_BUTTON;
      }
      
      return rawButton;
   };
}

namespace flair {
namespace internal {
namespace services {
namespace sdl {
   
   MouseService::MouseService() : _location({0,0})
   {
      memset(_prevButtons, 0, sizeof(_prevButtons));
      memset(_buttons, 0, sizeof(_buttons));
      clear();
   }
   
   void MouseService::movement(int X, int Y)
   {
      _movement.X = X;
      _movement.Y = Y;
   }
   
   void MouseService::movement(int * X, int * Y)
   {
      *X = _movement.X;
      *Y = _movement.Y;
   }
   
   void MouseService::location(int X, int Y)
   {
      _location.X = X;
      _location.Y = Y;
   }
   
   void MouseService::location(int * X, int * Y)
   {
      *X = _location.X;
      *Y = _location.Y;
   }
   
   void MouseService::button(uint32_t buttonCode, int state)
   {
      buttonCode = SDLtoMouse(buttonCode);
      if (buttonCode >= _BUTTON_COUNT) return;
      _buttons[buttonCode] = state;
   }
   
   void MouseService::button(uint32_t buttonCode, int * state)
   {
      if (buttonCode >= _BUTTON_COUNT) return;
      *state = _buttons[buttonCode];
   }
   
   
   void MouseService::buttonStates(std::function<void(uint32_t buttonCode, int currentState, int previousState)> callback)
   {
      for (uint32_t i = 0; i < _BUTTON_COUNT; ++i )
      {
         callback(i, _buttons[i], _prevButtons[i]);
      }
   }
   
   void MouseService::clear()
   {
      memcpy(_prevButtons, _buttons, sizeof(_prevButtons));
      memset(_buttons, 0, sizeof(_buttons));
      memset(&_movement, 0, sizeof(_movement));
   }
   
}}}}