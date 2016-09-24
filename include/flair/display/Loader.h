#ifndef flair_display_Loader_h
#define flair_display_Loader_h

#include "flair/flair.h"
#include "flair/display/DisplayObjectContainer.h"
#include "flair/net/URLRequest.h"
#include "flair/utils/ByteArray.h"
#include "flair/system/LoaderContext.h"

namespace flair {
namespace display {
   
   class Loader : public DisplayObjectContainer
   {
      friend class flair::allocator;
      
   protected:
      Loader();
      
   public:
      virtual ~Loader();

   // Properties
   public:
      std::shared_ptr<DisplayObject> content();
      
   // Methods
   public:
      void close();
      
      void load(std::shared_ptr<net::URLRequest> request, std::shared_ptr<system::LoaderContext> context = nullptr);
      
      void loadBytes(std::shared_ptr<utils::ByteArray> request, std::shared_ptr<system::LoaderContext> context = nullptr);
      
      void unload();
      
   // DisplayObjectContainer overrides
   public:
      std::shared_ptr<DisplayObject> addChild(std::shared_ptr<DisplayObject> child) override;
      std::shared_ptr<DisplayObject> addChildAt(std::shared_ptr<DisplayObject> child, int index) override;
      std::shared_ptr<DisplayObject> removeChild(std::shared_ptr<DisplayObject> child) override;
      std::shared_ptr<DisplayObject> removeChildAt(int index) override;
      void setChildIndex(const std::shared_ptr<DisplayObject>& child, int index) override;
      
   protected:
      std::shared_ptr<system::LoaderContext> _loaderContext;
      std::shared_ptr<DisplayObject> _content;
   };
   
}}

#endif
