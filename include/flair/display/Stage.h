#ifndef flair_display_Stage_h
#define flair_display_Stage_h

#include "flair/flair.h"
#include "flair/display/DisplayObjectContainer.h"

namespace flair { namespace desktop { class NativeApplication; } }

namespace flair {
namespace display {
   
   class Stage : public DisplayObjectContainer
   {
      friend class flair::allocator;
      
   protected:
      Stage();
      
   public:
      virtual ~Stage();
      
   // Properties
   public:
      int stageWidth();
      
      int stageHeight();
      
   // Methods
   public:
      
   // Internal
   protected:
      friend class flair::desktop::NativeApplication;
      void tick(float deltaSeconds) override;
      
      int _stageWidth;
      int _stageHeight;
   };
}}

#endif
