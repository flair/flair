#ifndef flair_internal_services_IKeyboardService_h
#define flair_internal_services_IKeyboardService_h

#include <cstdint>
#include <functional>

namespace flair {
   namespace internal {
      namespace services {
         
         class IKeyboardService
         {
         public:
            virtual void modifiers(int shift, int alt, int ctrl, int os) = 0;
            virtual void modifiers(int * shift, int * alt, int * ctrl, int * os) = 0;
            
            virtual void key(uint32_t keyCode, int state) = 0;
            virtual void key(uint32_t keyCode, int * state) = 0;
            
            virtual void activeKeys(std::function<void(uint32_t keyCode, int keyState)> callback) = 0;
            
            virtual void clear() = 0;
         };
         
      }
   }
}

#endif
