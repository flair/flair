#include "flair/system/PNGLoaderContext.h"
#include "flair/display/BitmapData.h"
#include "flair/display/Bitmap.h"
#include "flair/geom/Rectangle.h"
#include "flair/internal/services/IWorkerService.h"
#include "flair/internal/services/IAsyncIOService.h" // TODO: Worker Service should be self contained

#include "png.h"

namespace flair {
namespace system {
   
   using namespace flair::geom;
   using namespace flair::display;
   using namespace flair::internal::services;
   
   PNGLoaderContext::PNGLoaderContext()
   {
      
   }
   
   PNGLoaderContext::~PNGLoaderContext()
   {
      
   }
   
   void PNGLoaderContext::decode(std::shared_ptr<utils::ByteArray> bytes, std::function<void(std::shared_ptr<utils::ByteArray>)> callback)
   {
      callback(bytes);
   }
   
   void PNGLoaderContext::create(std::shared_ptr<utils::ByteArray> bytes, std::function<void(std::shared_ptr<display::DisplayObject>)> callback)
   {
      // TODO: Load a png using the worker service
      struct PNGWorkerResult : IAsyncWorkerRequest::IWorkerResult
      {
         int width;
         int height;
         uint8_t * pixels;
         
         PNGWorkerResult(int width, int height, uint8_t * pixels) : width(width), height(height), pixels(pixels) {};
         ~PNGWorkerResult() override { delete [] pixels; };
      };
      
      workerService->execute([this, bytes]() -> std::shared_ptr<IAsyncWorkerRequest::IWorkerResult> {
         // Do Work - Worker Thread
         
         // Check PNG Header
         bytes->position(0);
         uint8_t header[8] = { 0 };
         bytes->readBytes(header, 0, 8);
         if (png_sig_cmp((png_const_bytep)&header, 0, 8) == 0) {
            // Create the read and info structs
            png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
            png_infop info_ptr = png_create_info_struct(png_ptr);
            
            // Declare our data structs
            png_bytep * rowPtrs = nullptr;
            png_bytep * data = nullptr;
            
            // Error handeling
            if (setjmp(png_jmpbuf(png_ptr))) {
               png_destroy_read_struct(&png_ptr, &info_ptr,(png_infopp)0);
               delete [] rowPtrs;
               delete [] data;
               
               // Error out and send the main thread an empty result
               return std::make_shared<PNGWorkerResult>(0, 0, nullptr);
            }
            
            // Create our custom read function
            png_set_read_fn(png_ptr, (png_voidp)bytes.get(), [](png_structp pngPtr, png_bytep data, png_size_t length) {
               auto bytes = (utils::ByteArray *)png_get_io_ptr(pngPtr);
               bytes->readBytes(data, 0, length);
            });
            
            // Tell libpng that we already checked the header
            png_set_sig_bytes(png_ptr, 8);
            
            // Get the info from this png image
            png_read_info(png_ptr, info_ptr);
            png_uint_32 imgWidth =  png_get_image_width(png_ptr, info_ptr);
            png_uint_32 imgHeight = png_get_image_height(png_ptr, info_ptr);
            
            // Bits per CHANNEL! note: not per pixel!
            png_uint_32 bitdepth   = png_get_bit_depth(png_ptr, info_ptr);
            // Number of channels
            png_uint_32 channels   = png_get_channels(png_ptr, info_ptr);
            // Color type. (RGB, RGBA, Luminance, luminance alpha... palette... etc)
            png_uint_32 color_type = png_get_color_type(png_ptr, info_ptr);

            // Format conversion
            switch (color_type) {
               case PNG_COLOR_TYPE_PALETTE:
                  png_set_palette_to_rgb(png_ptr);
                  channels = 3;
                  break;
               case PNG_COLOR_TYPE_GRAY:
                  if (bitdepth < 8) png_set_expand_gray_1_2_4_to_8(png_ptr);
                  bitdepth = 8;
                  break;
            }
            
            // Store the alpha in it's own channel
            if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS)) {
               png_set_tRNS_to_alpha(png_ptr);
               channels+=1;
            }
            
            // Force bitdepth rounding
            if (bitdepth == 16) png_set_strip_16(png_ptr);
            
            // Data buffers
            rowPtrs = new png_bytep[imgHeight];
            data = new png_bytep[imgWidth * imgHeight * bitdepth * channels / 8];
            
            // Flip the image data so that it is in OpenGL format
            const unsigned int stride = imgWidth * bitdepth * channels / 8;
            for (size_t i = 0; i < imgHeight; i++) {
               //png_uint_32 q = (imgHeight - i - 1) * stride;
               png_uint_32 q = i * stride;
               rowPtrs[i] = (png_bytep)data + q;
            }
            
            // Read the image data
            png_read_image(png_ptr, rowPtrs);
            
            // Cleanup
            delete[] (png_bytep)rowPtrs;
            png_destroy_read_struct(&png_ptr, &info_ptr,(png_infopp)0);
            
            // Return our decoded png to the main thread
            return std::make_shared<PNGWorkerResult>(imgWidth, imgHeight, (uint8_t*)data);
         }
         
         return std::make_shared<PNGWorkerResult>(0, 0, nullptr);
      },
      [this, callback](std::shared_ptr<IAsyncWorkerRequest> request) {
         // Get Work - Main Thread
         auto png = std::static_pointer_cast<PNGWorkerResult>(request->result());
         if (png->pixels) {
            int width = png->width;
            int height = png->height;
            Rectangle rect(0, 0, width, height);
            auto format = BitmapDataFormat::BGRA;
            auto bitmapData = flair::make_shared<BitmapData>(width, height, format);
            
            bitmapData->lock();
            bitmapData->setPixels(rect, png->pixels, format);
            bitmapData->unlock();
            
            auto bitmap = flair::make_shared<Bitmap>(bitmapData);
            callback(bitmap);
         }
         else {
            callback(nullptr);
         }
      });
   }
   
}}
