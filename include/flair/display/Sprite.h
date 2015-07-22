#ifndef flair_display_Sprite_h
#define flair_display_Sprite_h

#include "flair/flair.h"
#include "flair/display/DisplayObjectContainer.h"

namespace flair {
   namespace display {
      
      class Sprite : public DisplayObjectContainer
      {
         friend class flair::allocator;
         
      protected:
         Sprite();
         
      public:
         virtual ~Sprite();
      };
      
   }
}

#endif
