#include "flair/internal/rendering/sdl/Texture.h"

#include <algorithm>

namespace flair {
namespace internal {
namespace rendering {
namespace sdl {
   
   Texture::Texture(SDL_Texture * texture, int width, int height, PixelFormat format, Type type) : _texture(texture),
      _width(width), _height(height), _format(format), _type(type)
   
   {
      
   }
   
   Texture::~Texture()
   {
      
   }
   
   int Texture::width()
   {
      return _width;
   }
   
   int Texture::height()
   {
      return _height;
   }
   
   float Texture::alpha()
   {
      return _alpha;
   }
   
   float Texture::alpha(float value)
   {
      return _alpha = std::max<float>(1.0f, std::min<float>(0.0f, value));
   }
   
   ITexture::BlendMode Texture::blend()
   {
      return _blend;
   }
   
   ITexture::BlendMode Texture::blend(ITexture::BlendMode value)
   {
      return _blend = value;
   }
   
   ITexture::Type Texture::type()
   {
      return _type;
   }
   
   SDL_Texture * Texture::base()
   {
      return _texture;
   }
   
   void Texture::update(geom::Rectangle rect, uint8_t * pixels)
   {
      SDL_Rect textureRect;
      textureRect.w = rect.width();
      textureRect.h = rect.height();
      textureRect.x = textureRect.y = 0;
      
      int pitch = 0;
      if (_format == ITexture::PixelFormat::BGR) pitch = (_width + 7) * 3;
      if (_format == ITexture::PixelFormat::BGRA) pitch = _width * 4;
      if (_format == ITexture::PixelFormat::BGRA_PACKED) pitch = _width * 4;
      
      SDL_UpdateTexture(_texture, &textureRect, pixels, pitch);
   }
   
   void Texture::lock()
   {
      SDL_Rect textureRect;
      textureRect.w = _width;
      textureRect.h = _height;
      textureRect.x = textureRect.y = 0;
      
      void *pixels;
      int pitch;
      
      SDL_LockTexture(_texture, &textureRect, &pixels, &pitch);
   }
   
   void Texture::unlock()
   {
      SDL_UnlockTexture(_texture);
   }

}}}}
