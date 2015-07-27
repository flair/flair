#ifndef flair_internal_services_sdl_KeyboardService_h
#define flair_internal_services_sdl_KeyboardService_h

#include "flair/internal/services/IKeyboardService.h"
#include "flair/ui/Keyboard.h"

namespace flair {
namespace internal {
namespace services {
namespace sdl {

   class KeyboardService : public IKeyboardService
   {
   public:
      void modifiers(int shift, int alt, int ctrl, int os) override;
      void modifiers(int * shift, int * alt, int * ctrl, int * os) override;
      
      void key(uint32_t keyCode, int state) override;
      void key(uint32_t keyCode, int * state) override;
      
      void activeKeys(std::function<void(uint32_t keyCode, int keyState)> callback) override;
      
      void clear() override;
      
   protected:
      struct Modifiers {
         int shift;
         int alt;
         int ctrl;
         int os;
      };
      
      int _keys[flair::ui::Keyboard::_KEY_COUNT];
      Modifiers _modifiers;
   };
   
}}}}

#endif
