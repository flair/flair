#ifndef flair_internal_services_sdl_MouseService_h
#define flair_internal_services_sdl_MouseService_h

#include "flair/internal/services/IMouseService.h"
#include "flair/ui/Keyboard.h"

namespace flair {
namespace internal {
namespace services {
namespace sdl {
   
   class MouseService : public IMouseService
   {
   public:
      MouseService();
      
      void movement(int X, int Y) override;
      void movement(int * X, int * Y) override;
      
      void location(int X, int Y) override;
      void location(int * X, int * Y) override;
      
      void button(uint32_t buttonCode, int state) override;
      void button(uint32_t buttonCode, int * state) override;
      
      void buttonStates(std::function<void(uint32_t buttonCode, int currentState, int previousState)> callback) override;
      
      void clear() override;
      
   protected:
      struct Position {
         int X;
         int Y;
      };
      
      int _buttons[IMouseService::_BUTTON_COUNT];
      int _prevButtons[IMouseService::_BUTTON_COUNT];
      
      Position _movement;
      Position _location;
   };
   
}}}}

#endif
