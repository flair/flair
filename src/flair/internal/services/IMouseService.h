#ifndef flair_internal_services_IMouseService_h
#define flair_internal_services_IMouseService_h

#include <cstdint>
#include <functional>

namespace flair {
namespace internal {
namespace services {
   
   class IMouseService
   {
   public:
      virtual void movement(int X, int Y) = 0;
      virtual void movement(int * X, int * Y) = 0;
      
      virtual void location(int X, int Y) = 0;
      virtual void location(int * X, int * Y) = 0;
      
      virtual void button(uint32_t buttonCode, int state) = 0;
      virtual void button(uint32_t buttonCode, int * state) = 0;
      
      virtual void buttonStates(std::function<void(uint32_t buttonCode, int currentState, int previousState)> callback) = 0;
      
      virtual void clear() = 0;
      
   public:
      enum {
         LEFT_BUTTON = 0,
         MIDDLE_BUTTON = 1,
         RIGHT_BUTTON = 2,
         
         _BUTTON_COUNT
      };
   };
   
}}}

#endif
