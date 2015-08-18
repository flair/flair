#ifndef flair_display_Bitmap_h
#define flair_display_Bitmap_h

#include "flair/flair.h"
#include "flair/display/BitmapData.h"
#include "flair/display/DisplayObject.h"

namespace flair {
namespace display {
   
   class Bitmap : public DisplayObject
   {
      friend class flair::allocator;
      
   protected:
      Bitmap(std::shared_ptr<BitmapData> bitmapData);
      
   public:
      virtual ~Bitmap();
      
      
   // Properties
   public:
      std::shared_ptr<BitmapData> bitmapData();
      std::shared_ptr<BitmapData> bitmapData(std::shared_ptr<BitmapData> value);
      
      float width() const override;
      float height() const override;
   
   // Internal
   protected:
      void render(RenderSupport * support, float parentAlpha, geom::Matrix parentTransform) override;
      
      
   protected:
      std::shared_ptr<BitmapData> _bitmapData;
   };
   
}}

#endif
