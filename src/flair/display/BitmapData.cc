#include "flair/display/BitmapData.h"
#include "flair/internal/services/IRenderService.h"
#include "flair/internal/rendering/ITexture.h"

namespace flair {
namespace display {
   
   using namespace flair::internal::rendering;
   
   flair::internal::services::IRenderService * BitmapData::renderService = nullptr;
   
   BitmapData::BitmapData(int width, int height, BitmapDataFormat format)
   {
      texture = renderService->createTexture(width, height, ITexture::PixelFormat::BGRA, ITexture::Type::STATIC);
   }
   
   BitmapData::~BitmapData()
   {
      renderService->destroyTexture(texture);
   }
   
   float BitmapData::width() const
   {
      return texture->width();
   }
   
   float BitmapData::height() const
   {
      return texture->height();
   }
   
   void BitmapData::lock()
   {
      texture->lock();
   }
   
   void BitmapData::setPixels(geom::Rectangle rect, std::shared_ptr<utils::ByteArray> pixels, BitmapDataFormat format)
   {
      uint8_t * bytes = new uint8_t[pixels->length()];
      
      pixels->readBytes(bytes, 0, pixels->length());
      texture->update(rect, bytes);
      
      delete[] bytes;
   }
   
   void BitmapData::setPixels(geom::Rectangle rect, std::vector<uint32_t> pixels, BitmapDataFormat format)
   {
      auto bytes = (uint8_t*)pixels.data();
      texture->update(rect, bytes);
   }
   
   void BitmapData::setPixels(geom::Rectangle rect, uint8_t * pixels, BitmapDataFormat format)
   {
      texture->update(rect, pixels);
   }
   
   void BitmapData::unlock()
   {
      texture->unlock();
   }
   
}}