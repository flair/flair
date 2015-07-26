#ifndef flair_events_KeyboardEvent_h
#define flair_events_KeyboardEvent_h

#include "flair/flair.h"
#include "flair/events/Event.h"

namespace flair {
   namespace events {
      
      class KeyboardEvent : public Event
      {
         friend class flair::allocator;
         
      protected:
         KeyboardEvent(const char * type, bool bubbles = false, bool cancelable = false, uint32_t charCode = 0, uint32_t keyCode = 0, uint32_t keyLocation = 0, bool ctrlKey = false, bool altKey = false, bool shiftKey = false, bool controlKey = false, bool commandKey = false);
         
      public:
         virtual ~KeyboardEvent();
      
      
      // Events
      public:
         static const char* KEY_DOWN;
         static const char* KEY_UP;
         
      
      // Properties
      public:
         bool altKey();
         
         uint32_t charCode();
         
         bool commandKey();
         
         bool controlKey();
         
         bool ctrlKey();
         
         uint32_t keyCode();
         
         uint32_t keyLocation();
         
         bool shiftKey();
      
      
      // Methods
      public:
         std::shared_ptr<Event> clone() override;
         
         std::string toString() const override;
      
      
      protected:
         bool _altKey;
         uint32_t _charCode;
         bool _commandKey;
         bool _controlKey;
         bool _ctrlKey;
         uint32_t _keyCode;
         uint32_t _keyLocation;
         bool _shiftKey;
      };
   }
}

#endif
