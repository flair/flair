#ifndef flair_internal_rendering_Texture_h
#define flair_internal_rendering_Texture_h

#include "flair/internal/rendering/ITexture.h"

#include "sdl.h"

namespace flair {
namespace internal {
namespace rendering {
namespace sdl {
   
   class Texture : public ITexture
   {
   public:
      Texture(SDL_Texture * texture, int width, int height, PixelFormat format, Type type);
      virtual ~Texture();
      
   // Properties
   public:
      int width() override;
      
      int height() override;
      
      float alpha() override;
      float alpha(float value) override;
      
      BlendMode blend() override;
      BlendMode blend(BlendMode value) override;
      
      Type type() override;
      
      SDL_Texture * base();
      
   // Methods
   public:
      void update(geom::Rectangle rect, uint8_t const* pixels) override;
      
      void lock() override;
      
      void unlock() override;
      
   protected:
      SDL_Texture * _texture;
      int _width;
      int _height;
      PixelFormat _format;
      Type _type;
      float _alpha;
      BlendMode _blend;
   };
   
}}}}

#endif
