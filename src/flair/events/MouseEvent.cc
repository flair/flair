#include "flair/events/MouseEvent.h"

namespace flair {
namespace events {
   
   MouseEvent::MouseEvent(const char * type, bool bubbles, bool cancelable, float localX, float localY, float movementX, float movementY, std::shared_ptr<Object> relatedObject, bool buttonDown, int delta, int clickCount, bool ctrlKey, bool altKey, bool shiftKey, bool controlKey, bool commandKey)
      : Event(type, bubbles, cancelable), _localX(localX), _localY(localY), _movementX(movementX), _movementY(movementY), _stageX(localX), _stageY(localY), _relatedObject(relatedObject),
         _buttonDown(buttonDown), _delta(delta), _clickCount(clickCount), _ctrlKey(ctrlKey), _altKey(altKey), _shiftKey(shiftKey), _controlKey(controlKey), _commandKey(commandKey)
   {
      
   }
   
   MouseEvent::~MouseEvent()
   {
      
   }
   
   bool MouseEvent::buttonDown()
   {
      return _buttonDown;
   }
   
   int MouseEvent::clickCount()
   {
      return _clickCount;
   }
   
   int MouseEvent::delta()
   {
      return _delta;
   }
   
   float MouseEvent::localX()
   {
      return _localX;
   }
   
   float MouseEvent::localY()
   {
      return _localY;
   }
   
   float MouseEvent::movementX()
   {
      return _movementX;
   }
   
   float MouseEvent::movementY()
   {
      return _movementY;
   }
   
   std::shared_ptr<Object> MouseEvent::relatedObject()
   {
      return _relatedObject;
   }
   
   float MouseEvent::stageX()
   {
      return _stageX;
   }
   
   float MouseEvent::stageY()
   {
      return _stageY;
   }
   
   bool MouseEvent::altKey()
   {
      return _altKey;
   }
   
   bool MouseEvent::commandKey()
   {
      return _commandKey;
   }
   
   bool MouseEvent::controlKey()
   {
      return _controlKey;
   }
   
   bool MouseEvent::ctrlKey()
   {
      return _ctrlKey;
   }
   
   bool MouseEvent::shiftKey()
   {
      return _shiftKey;
   }
   
   std::shared_ptr<Event> MouseEvent::clone()
   {
      return std::static_pointer_cast<Event>(flair::make_shared<MouseEvent>(_type.c_str(), _bubbles, _cancelable, _localX, _localY, _movementX, _movementY, _relatedObject, _buttonDown, _delta, _clickCount, _ctrlKey, _altKey, _shiftKey, _controlKey, _commandKey));
   }
   
   std::string MouseEvent::toString() const
   {
      return "[flair.events.MouseEvent MouseEvent]";
   }
   
   const char * MouseEvent::CLICK = "click";
   const char * MouseEvent::DOUBLE_CLICK = "doubleClick";
   const char * MouseEvent::MIDDLE_CLICK = "middleClick";
   const char * MouseEvent::MIDDLE_MOUSE_DOWN = "middleMouseDown";
   const char * MouseEvent::MIDDLE_MOUSE_UP = "middleMouseUp";
   const char * MouseEvent::MOUSE_DOWN = "mouseDown";
   const char * MouseEvent::MOUSE_MOVE = "mouseMove";
   const char * MouseEvent::MOUSE_OUT = "mouseOut";
   const char * MouseEvent::MOUSE_OVER = "mouseOver";
   const char * MouseEvent::MOUSE_UP = "mouseUp";
   const char * MouseEvent::MOUSE_WHEEL = "mouseWheel";
   const char * MouseEvent::RIGHT_CLICK = "rightClick";
   const char * MouseEvent::RIGHT_MOUSE_DOWN = "rightMouseDown";
   const char * MouseEvent::RIGHT_MOUSE_UP = "rightMouseUp";
   const char * MouseEvent::ROLL_OUT = "rollOut";
   const char * MouseEvent::ROLL_OVER = "rollOver";
}}