#include "flair/display/Bitmap.h"

namespace flair {
namespace display {
   
   Bitmap::Bitmap(std::shared_ptr<BitmapData> bitmapData) : _bitmapData(bitmapData)
   {
      
   }
   
   Bitmap::~Bitmap()
   {
      
   }
   
   std::shared_ptr<BitmapData> Bitmap::bitmapData()
   {
      return _bitmapData;
   }
   
   std::shared_ptr<BitmapData> Bitmap::bitmapData(std::shared_ptr<BitmapData> value)
   {
      return _bitmapData = value;
   }
   
   float Bitmap::width() const
   {
      return _bitmapData->width();
   }
   
   float Bitmap::height() const
   {
      return _bitmapData->height();
   }
   
   void Bitmap::render(RenderSupport * support, float parentAlpha, geom::Matrix parentTransform)
   {
      geom::Matrix transform = transformationMatrix() * parentTransform;
      support->renderBitmap(shared<Bitmap>(), transform);
   }

}}
