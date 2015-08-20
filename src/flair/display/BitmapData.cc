#include "flair/display/BitmapData.h"
#include "flair/internal/services/IRenderService.h"
#include "flair/internal/rendering/ITexture.h"
#include "flair/internal/utils/ByteArrayProxy.h"

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
      flair::internal::utils::ByteArrayProxy proxy(pixels);
      
      int bytesPerPixel = 8; // TODO: Correct format calculation
      assert(rect.width() * rect.height() * bytesPerPixel <= proxy.length() && "Pixel buffer is not large enough for this texture");
      
      texture->update(rect, proxy.bytes());
   }
   
   void BitmapData::setPixels(geom::Rectangle rect, std::vector<uint32_t> pixels, BitmapDataFormat format)
   {
      int bytesPerPixel = 8; // TODO: Correct format calculation
      assert(rect.width() * rect.height() * bytesPerPixel <= pixels.size() * 4 && "Pixel buffer is not large enough for this texture");
      
      auto bytes = (uint8_t*)pixels.data();
      texture->update(rect, bytes);
   }
   
   void BitmapData::setPixels(geom::Rectangle rect, uint8_t const* pixels, size_t length, BitmapDataFormat format)
   {
      int bytesPerPixel = 8; // TODO: Correct format calculation
      assert(rect.width() * rect.height() * bytesPerPixel <= length && "Pixel buffer is not large enough for this texture");
      
      texture->update(rect, pixels);
   }
   
   void BitmapData::unlock()
   {
      texture->unlock();
   }
   
}}