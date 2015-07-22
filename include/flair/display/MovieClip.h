#ifndef flair_display_MovieClip_h
#define flair_display_MovieClip_h

#include "flair/flair.h"
#include "flair/display/Sprite.h"

namespace flair {
   namespace display {
      
      class MovieClip : public Sprite
      {
         friend class flair::allocator;
         
      protected:
         MovieClip();
         
      public:
         virtual ~MovieClip();
         
      }
   }
}
#endif
