#include "flair/internal/services/sdl/RenderService.h"
#include "flair/internal/services/sdl/WindowService.h"
#include "flair/internal/rendering/sdl/Texture.h"

#include <cmath>

namespace flair {
namespace internal {
namespace services {
namespace sdl {
   
   using namespace rendering;
   using namespace rendering::sdl;
   
   RenderService::RenderService() :
      _renderer(nullptr)
   {
      
   }
   
   RenderService::~RenderService()
   {
      if (_renderer) SDL_DestroyRenderer(_renderer);
   }
   
   SDL_Renderer * RenderService::renderer()
   {
      return _renderer;
   }
   
   void RenderService::create(IWindowService * windowService, bool vsync)
   {
      uint32_t sdlFlags = SDL_RENDERER_ACCELERATED;
      if (vsync) sdlFlags |= SDL_RENDERER_PRESENTVSYNC;
      
      SDL_Window * window = static_cast<WindowService*>(windowService)->window();
      
      _renderer = SDL_CreateRenderer(window, 0, sdlFlags);
   }
   
   void RenderService::clear()
   {
      SDL_RenderClear(_renderer);
   }
   
   void RenderService::present()
   {
      SDL_RenderPresent(_renderer);
   }
   
   rendering::ITexture * RenderService::createTexture(int width, int height, ITexture::PixelFormat format, rendering::ITexture::Type type)
   {
      Uint32 sdlFormat = 0;
      if (format == ITexture::PixelFormat::BGR) sdlFormat = SDL_PIXELFORMAT_BGR888;
      if (format == ITexture::PixelFormat::BGRA) sdlFormat = SDL_PIXELFORMAT_ABGR8888;
      if (format == ITexture::PixelFormat::BGRA_PACKED) sdlFormat = SDL_PIXELFORMAT_ARGB1555;
      
      int access = 0;
      if (type == ITexture::Type::STATIC) access = SDL_TEXTUREACCESS_STATIC;
      if (type == ITexture::Type::STREAMING) access = SDL_TEXTUREACCESS_STREAMING;
      if (type == ITexture::Type::RENDER_TARGET) access = SDL_TEXTUREACCESS_TARGET;
      
      SDL_Texture * native = SDL_CreateTexture(_renderer, sdlFormat, access, width, height);
      SDL_SetTextureBlendMode(native, SDL_BLENDMODE_BLEND);
      return new Texture(native, width, height, format, type);
   }
   
   void RenderService::renderTexture(rendering::ITexture * texture, geom::Rectangle srcRect, geom::Rectangle dstRect)
   {
      Texture * native = static_cast<Texture*>(texture);
      
      SDL_Rect source;
      source.w = srcRect.width();
      source.h = srcRect.height();
      source.x = srcRect.x();
      source.y = srcRect.y();
      
      SDL_Rect destination;
      destination.w = dstRect.width();
      destination.h = dstRect.height();
      destination.x = dstRect.x();
      destination.y = dstRect.y();
      
      SDL_RenderCopy(_renderer, native->base(), &source, &destination);
   }
   
   void RenderService::renderTexture(rendering::ITexture * texture, geom::Rectangle srcRect, geom::Matrix transform)
   {
      Texture * native = static_cast<Texture*>(texture);
      
      float x = transform.tx();
      float y = transform.ty();
      float a = transform.a();
      float c = transform.c();
      float b = transform.b();
      float d = transform.d();
      float scaleX = std::sqrt((a*a) + (c*c));
      float scaleY = std::sqrt((b*b) + (d*d));
      float rotation = std::atan(-b/a) * (180.0f/M_PI);
      float sign = std::atan(-c / a);
      float rad = std::acos(a / scaleX);
      float deg = rad * (180.0f/M_PI);
      
      if (deg > 90 && sign > 0) {
         rotation = (360 - deg) * (M_PI/180.0f);
      }
      else if (deg < 90 && sign < 0)
      {
         rotation = (360 - deg) * (M_PI/180.0f);
      }
      else
      {
         rotation = rad;
      }
      rotation = rotation * (180.0f/M_PI);
      
      SDL_Rect source;
      source.w = srcRect.width();
      source.h = srcRect.height();
      source.x = srcRect.x();
      source.y = srcRect.y();
      
      SDL_Rect destination;
      destination.w = source.w * scaleX;
      destination.h = source.h * scaleY;
      destination.x = x;
      destination.y = y;
      
      SDL_Point pivot;
      pivot.x = 0;
      pivot.y = 0;
      
      //SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);
      SDL_RenderCopyEx(_renderer, native->base(), &source, &destination, rotation, &pivot, SDL_FLIP_NONE);
   }
   
   void RenderService::destroyTexture(rendering::ITexture * texture)
   {
      Texture * native = static_cast<Texture*>(texture);
      SDL_DestroyTexture(native->base());
   }

}}}}
