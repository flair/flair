#ifndef flair_display_Image_h
#define flair_display_Image_h

#include "flair/flair.h"
#include "flair/display/DisplayObject.h"

namespace flair {
   namespace display {
      
      class Image : public DisplayObject
      {
         friend class flair::allocator;
       
      protected:
         Image();
         
      public:
         virtual ~Image();
         
      // Methods
      public:
         std::string toString() const override;
      };
      
   }
}

#endif
