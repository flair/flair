#ifndef flair_internal_rendering_ITexture_h
#define flair_internal_rendering_ITexture_h

#include "flair/geom/Rectangle.h"

#include <cstdint>

namespace flair {
namespace internal {
namespace rendering {
   
   class ITexture
   {
   public:
      enum class PixelFormat {
         BGRA,
         BGRA_PACKED,
         BGR
      };
      
      enum class BlendMode {
         NONE,
         ALPHA,
         ADDITIVE,
         MODULATE
      };
      
      enum class Type {
         STATIC,
         STREAMING,
         RENDER_TARGET
      };
      
      
   // Properties
   public:
      virtual int width() = 0;
      
      virtual int height() = 0;
      
      virtual float alpha() = 0;
      virtual float alpha(float value) = 0;
      
      virtual BlendMode blend() = 0;
      virtual BlendMode blend(BlendMode value) = 0;
      
      virtual Type type() = 0;
      
      
   // Methods
   public:
      
      virtual void update(geom::Rectangle rect, uint8_t const* pixels) = 0;
      
      virtual void lock() = 0;
      
      virtual void unlock() = 0;
   };
   
}}}

#endif
