#include "flair/flair.h"
#include "flair/display/Stage.h"
#include "flair/events/Event.h"
#include "flair/events/KeyboardEvent.h"
#include "flair/filesystem/File.h"
#include "flair/ui/Keyboard.h"
#include "flair/desktop/NativeApplication.h"

using flair::JSON;
using flair::display::Stage;
using flair::events::Event;
using flair::events::KeyboardEvent;
using flair::filesystem::File;
using flair::ui::Keyboard;
using flair::desktop::NativeApplication;


class GameStage : public Stage
{
   friend class flair::allocator;

protected:
   GameStage()
   {
      addEventListener(Event::ACTIVATE, &GameStage::onActivated, this);
      addEventListener(Event::DEACTIVATE, &GameStage::onDeactivated, this);
      addEventListener(Event::ENTER_FRAME, &GameStage::onEnterFrame, this, false, 0, true);
      addEventListener(KeyboardEvent::KEY_DOWN, &GameStage::onKeyDown, this, false, 0, true);
   };

public:
   virtual ~GameStage() {};
   
protected:
   std::shared_ptr<File> _file;
   
public:
   void onActivated(std::shared_ptr<Event> e)
   {
      std::cout << "Activated" << std::endl;
      
      std::cout << "Application Directory: " << File::applicationDirectory()->name() << std::endl;
      _file = flair::make_shared<File>("/Users/axon/Projects/C/flair/premake.lua");
      
      _file->addEventListener(Event::COMPLETE, &GameStage::onFileLoaded, this);
      _file->load();
      
   }
   
   void onDeactivated(std::shared_ptr<Event> e)
   {
      std::cout << "Deactivated" << std::endl;
   }
   
   void onEnterFrame(std::shared_ptr<Event> e)
   {
      
   }
   
   void onKeyDown(std::shared_ptr<Event> e)
   {
      auto keyboardEvent = std::dynamic_pointer_cast<KeyboardEvent>(e);
      std::cout << "On Key Down: " << keyboardEvent->keyCode() << " with shift: " << keyboardEvent->shiftKey() << std::endl;
      std::cout << "Caps Lock: " << Keyboard::capsLock() << " Num Lock: " << Keyboard::numLock() << std::endl;
      
      if (keyboardEvent->keyCode() == Keyboard::ESCAPE) {
         auto nativeApp = NativeApplication::nativeApplication();
         nativeApp->exit();
      }
      else if (keyboardEvent->keyCode() == Keyboard::F) {
         _file->load();
      }
   }
   
   void onFileLoaded(std::shared_ptr<Event> e)
   {
      auto data = _file->data();
      auto text = data->readUTFBytes(data->length());
      std::cout << "File Loaded:" << std::endl;
      std::cout << text << std::endl;
   }
};

int main(int argc, const char* argv[])
{
   JSON applicationDescriptor = JSON::Object {
      {"id", "FlairReferenceApplication"},
      {"version", "0.0.1"},
      {"filename", "Reference"},
      {"name", "Flair Reference Application"},
      {"description", "A reference application for flair"},
      {"copyright", "Copyright (c) 2015 thejustinwalsh LLC"},
      {"initialWindow", JSON::Object {
         {"title", "Flair"},
         {"visible", true},
         {"minSize", "320 240"},
         {"maxSize", "1920 1080"},
         {"resizeable", true},
         {"maximizable", true},
         {"minimizable", true},
         {"width", 1280},
         {"height", 720},
         {"x", -1},
         {"y", -1},
         {"fullsreen", false},
         {"vsync", false}, // DESKTOP ONLY
         {"requestedDisplayResolution", "high"}, // "standard" || "high"
         {"aspectRatio", "landscape"}, // MOBILE ONLY: "portrait" || "landscape" || ""
         {"autoOrients", true} // MOBILE ONLY
      }}
   };
   
   auto game = flair::make_shared<GameStage>();
   flair::run(applicationDescriptor, game);
}
