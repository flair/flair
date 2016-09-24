#include "flair/display/Bitmap.h"

namespace flair {
namespace display {
   
   Bitmap::Bitmap(std::shared_ptr<BitmapData> bitmapData) : _bitmapData(bitmapData)
   {
      _width = _bitmapData->width();
      _height = _bitmapData->height();
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
   
   void Bitmap::render(RenderSupport * support, float parentAlpha, geom::Matrix parentTransform)
   {
      geom::Matrix transform = parentTransform * transformationMatrix();
      support->renderBitmap(shared<Bitmap>(), transform);
   }

}}
