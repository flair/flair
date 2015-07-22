#include "flair/Object.h"

namespace flair {
   
   Object::Object()
   {
      _shared = std::shared_ptr<Object>(this);
   }

   Object::~Object()
   {
      
   }
   
   std::string Object::toString() const
   {
      return "[Object object]";
   }

}