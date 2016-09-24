#include "flair/display/Loader.h"
#include "flair/filesystem/File.h"
#include "flair/utils/ByteArray.h"
#include "flair/system/PNGLoaderContext.h"

#include <stdexcept>

namespace {
   std::shared_ptr<flair::system::LoaderContext> createLoaderContext(std::string ext)
   {
      if (ext == ".png") return flair::make_shared<flair::system::PNGLoaderContext>();
      
      return flair::make_shared<flair::system::LoaderContext>();
   }
}

namespace flair {
namespace display {

   Loader::Loader()
   {
      
   }
   
   Loader::~Loader()
   {
      
   }
   
   std::shared_ptr<DisplayObject> Loader::content()
   {
      return _content;
   }
   
   void Loader::close()
   {
      
   }
   
   void Loader::load(std::shared_ptr<net::URLRequest> request, std::shared_ptr<system::LoaderContext> context)
   {
      if (!request->isFilePath()) throw std::runtime_error("Only file urls currently supported");
      
      auto file = flair::make_shared<filesystem::File>(request->url());
      if (!context) context = createLoaderContext(file->extension());
      
      file->addEventListener(events::Event::ERROR, [this, file](std::shared_ptr<events::Event> e) {
         dispatchEvent(flair::make_shared<events::Event>(events::Event::ERROR));
      }, false, 0, true);
      
      file->addEventListener(events::Event::COMPLETE, [this, file, context](std::shared_ptr<events::Event> e) {
         loadBytes(file->data(), context);
      }, false, 0, true);
      
      file->load();
   }
   
   void Loader::loadBytes(std::shared_ptr<utils::ByteArray> request, std::shared_ptr<system::LoaderContext> context)
   {
      _loaderContext = context;
      _loaderContext->create(request, [this](std::shared_ptr<display::DisplayObject> displayObject) {
         if (displayObject) {
            _content = displayObject;
            
            DisplayObjectContainer::addChildAt(_content, _children.size());
            dispatchEvent(flair::make_shared<events::Event>(events::Event::COMPLETE));
         }
         else {
            dispatchEvent(flair::make_shared<events::Event>(events::Event::ERROR));
         }
         
         _loaderContext = nullptr;
      });
   }
   
   void Loader::unload()
   {
      if (_content) {
         DisplayObjectContainer::removeChild(_content);
         _content = nullptr;
      }
   }
   
   std::shared_ptr<DisplayObject> Loader::addChild(std::shared_ptr<DisplayObject> child)
   {
      throw std::runtime_error("Loader only supports a single child created from the load method");
   }
   
   std::shared_ptr<DisplayObject> Loader::addChildAt(std::shared_ptr<DisplayObject> child, int index)
   {
      throw std::runtime_error("Loader only supports a single child created from the load method");
   }
   
   std::shared_ptr<DisplayObject> Loader::removeChild(std::shared_ptr<DisplayObject> child)
   {
      throw std::runtime_error("Loader only supports a single child created from the load method");
   }
   
   std::shared_ptr<DisplayObject> Loader::removeChildAt(int index)
   {
      throw std::runtime_error("Loader only supports a single child created from the load method");
   }
   
   void Loader::setChildIndex(const std::shared_ptr<DisplayObject>& child, int index)
   {
      throw std::runtime_error("Loader only supports a single child created from the load method");
   }
   
}}
