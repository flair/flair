#ifndef flair_events_MouseEvent_h
#define flair_events_MouseEvent_h

#include "flair/flair.h"
#include "flair/events/Event.h"

namespace flair {
namespace events {
   
   class MouseEvent : public Event
   {
      friend class flair::allocator;
      
   protected:
      MouseEvent(const char * type, bool bubbles = false, bool cancelable = false, float localX = std::numeric_limits<float>::quiet_NaN(), float localY = std::numeric_limits<float>::quiet_NaN(), float movementX = std::numeric_limits<float>::quiet_NaN(), float movementY = std::numeric_limits<float>::quiet_NaN(), std::shared_ptr<Object> relatedObject = nullptr, bool buttonDown = false, int delta = 0, int clickCount = 0, bool ctrlKey = false, bool altKey = false, bool shiftKey = false, bool controlKey = false, bool commandKey = false);
      
   public:
      virtual ~MouseEvent();
      
      
   // Events
   public:
      static const char * CLICK;
      static const char * DOUBLE_CLICK;
      static const char * MIDDLE_CLICK;
      static const char * MIDDLE_MOUSE_DOWN;
      static const char * MIDDLE_MOUSE_UP;
      static const char * MOUSE_DOWN;
      static const char * MOUSE_MOVE;
      static const char * MOUSE_OUT;
      static const char * MOUSE_OVER;
      static const char * MOUSE_UP;
      static const char * MOUSE_WHEEL;
      static const char * RIGHT_CLICK;
      static const char * RIGHT_MOUSE_DOWN;
      static const char * RIGHT_MOUSE_UP;
      static const char * ROLL_OUT;
      static const char * ROLL_OVER;
      
      
   // Properties
   public:
      bool buttonDown();
      
      int clickCount();
      
      int delta();
      
      float localX();
      
      float localY();
      
      float movementX();
      
      float movementY();
      
      std::shared_ptr<Object> relatedObject();
      
      float stageX();
      
      float stageY();
      
      bool altKey();
      
      bool commandKey();
      
      bool controlKey();
      
      bool ctrlKey();
      
      bool shiftKey();
      
      
   // Methods
   public:
      std::shared_ptr<Event> clone() override;
      
      std::string toString() const override;
      
      
   protected:
      bool _buttonDown;
      int _clickCount;
      int _delta;
      float _localX;
      float _localY;
      float _movementX;
      float _movementY;
      std::shared_ptr<Object> _relatedObject;
      float _stageX;
      float _stageY;
      bool _altKey;
      bool _commandKey;
      bool _controlKey;
      bool _ctrlKey;
      bool _shiftKey;
   };
}}

#endif
