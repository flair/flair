#ifndef flair_display_BitmapData_h
#define flair_display_BitmapData_h

#include "flair/flair.h"
#include "flair/utils/ByteArray.h"
#include "flair/geom/Rectangle.h"

namespace flair { namespace display { class RenderSupport; } }
namespace flair { namespace desktop { class NativeApplication; } }
namespace flair { namespace internal { namespace services { class IRenderService; } } }
namespace flair { namespace internal { namespace rendering { class ITexture; } } }

namespace flair {
namespace display {
   
   enum class BitmapDataFormat {
      BGRA,
      BGRA_PACKED,
      BGR_PACKED,
      COMPRESSED,
      COMPRESSED_ALPHA,
      RGBA_HALF_FLOAT
   };
   
   class BitmapData : public Object
   {
      friend class flair::allocator;
      
   protected:
      BitmapData(int width = 0, int height = 0, BitmapDataFormat format = BitmapDataFormat::BGRA);
      
   public:
      virtual ~BitmapData();
      
   
   // Properties
   public:
      float width() const;
      float height() const;
      
   // Methods
   public:
      void lock();
      
      void setPixels(geom::Rectangle rect, std::shared_ptr<utils::ByteArray> pixels, BitmapDataFormat format = BitmapDataFormat::BGRA);
      
      void setPixels(geom::Rectangle rect, std::vector<uint32_t> pixels, BitmapDataFormat format = BitmapDataFormat::BGRA);
      
      void setPixels(geom::Rectangle rect, uint8_t const* pixels, size_t length, BitmapDataFormat format = BitmapDataFormat::BGRA);
      
      void unlock();
   
   
   // Internal
   protected:
      friend class flair::desktop::NativeApplication;
      static flair::internal::services::IRenderService * renderService;
      
      friend class flair::display::RenderSupport;
      flair::internal::rendering::ITexture * texture;
   };
   
}}

#endif
