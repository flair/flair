#include "flair/events/KeyboardEvent.h"

namespace flair {
   namespace events {
      
      KeyboardEvent::KeyboardEvent(const char* type, bool bubbles, bool cancelable, uint32_t charCode, uint32_t keyCode, uint32_t keyLocation, bool ctrlKey, bool altKey, bool shiftKey, bool controlKey, bool commandKey)
         : Event(type, bubbles, cancelable), _charCode(charCode), _keyCode(keyCode), _keyLocation(keyLocation), _ctrlKey(ctrlKey),
           _altKey(altKey), _shiftKey(shiftKey), _controlKey(controlKey), _commandKey(commandKey)
      {
         
      }
      
      KeyboardEvent::~KeyboardEvent()
      {
         
      }
      
      bool KeyboardEvent::altKey()
      {
         return _altKey;
      }
      
      uint32_t KeyboardEvent::charCode()
      {
         return _charCode;
      }
      
      bool KeyboardEvent::commandKey()
      {
         return _commandKey;
      }
      
      bool KeyboardEvent::controlKey()
      {
         return _controlKey;
      }
      
      bool KeyboardEvent::ctrlKey()
      {
         return _ctrlKey;
      }
      
      uint32_t KeyboardEvent::keyCode()
      {
         return _keyCode;
      }
      
      uint32_t KeyboardEvent::keyLocation()
      {
         return _keyLocation;
      }
      
      bool KeyboardEvent::shiftKey()
      {
         return _shiftKey;
      }
      
      std::shared_ptr<Event> KeyboardEvent::clone()
      {
         return std::static_pointer_cast<Event>(flair::make_shared<KeyboardEvent>(_type.c_str(), _bubbles, _cancelable, _charCode, _keyCode, _keyLocation, _ctrlKey, _altKey, _shiftKey, _controlKey, _commandKey));
      }
      
      std::string KeyboardEvent::toString() const
      {
         return "[flair.events.KeyboardEvent KeyboardEvent]";
      }
      
      const char* KeyboardEvent::KEY_DOWN = "keyDown";
      const char* KeyboardEvent::KEY_UP = "keyUp";
   }
}
