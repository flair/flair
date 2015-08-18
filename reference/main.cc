#include "flair/flair.h"
#include "flair/display/Stage.h"
#include "flair/display/Loader.h"
#include "flair/display/Bitmap.h"
#include "flair/events/Event.h"
#include "flair/events/KeyboardEvent.h"
#include "flair/filesystem/File.h"
#include "flair/net/URLRequest.h"
#include "flair/ui/Keyboard.h"
#include "flair/desktop/NativeApplication.h"

#include <cmath>

using flair::JSON;
using flair::display::Stage;
using flair::display::Loader;
using flair::display::Bitmap;
using flair::events::Event;
using flair::events::KeyboardEvent;
using flair::filesystem::File;
using flair::net::URLRequest;
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
      addEventListener(Event::ENTER_FRAME, &GameStage::onEnterFrame, this, false, 0, true);     // Weak Reference
      addEventListener(KeyboardEvent::KEY_DOWN, &GameStage::onKeyDown, this, false, 0, true);   // Weak Reference
      addEventListener(KeyboardEvent::KEY_UP, &GameStage::onKeyUp, this, false, 0, true);       // Weak Reference
   };

public:
   virtual ~GameStage() {};
   
public:
   void onActivated(std::shared_ptr<Event> e)
   {
      std::cout << "Activated" << std::endl;
      std::cout << "Application Directory: " << File::applicationDirectory()->name() << std::endl;
      
      // Load the background
      std::shared_ptr<URLRequest> backgroundUrl = flair::make_shared<URLRequest>(File::applicationDirectory()->url() + std::string("/uncolored_castle.png"));
      background = flair::make_shared<Loader>();
      background->addEventListener(Event::COMPLETE, [this](std::shared_ptr<Event> e) {
         auto bitmap = std::dynamic_pointer_cast<Bitmap>(background->getChildAt(0));
         auto copy = flair::make_shared<Bitmap>(bitmap->bitmapData());
         copy->x(bitmap->width());
         addChildAt(copy, 0);
      }, false, 0, true); // A "WeakReference" for a lambda means execute it once
      addChild(background);
      background->load(backgroundUrl);
      
      // Load an alien
      std::shared_ptr<URLRequest> alienUrl = flair::make_shared<URLRequest>(File::applicationDirectory()->url() + std::string("/alienPink_swim1.png"));
      alien = flair::make_shared<Loader>();
      alien->addEventListener(Event::COMPLETE, [this](std::shared_ptr<Event> e) {
         alienBitmap = std::dynamic_pointer_cast<Bitmap>(alien->getChildAt(0));
      }, false, 0, true); // A "WeakReference" for a lambda means execute it once
      addChild(alien);
      alien->x(50);
      alien->y(stageHeight()/2);
      alien->load(alienUrl);
   }
   
   void onDeactivated(std::shared_ptr<Event> e)
   {
      std::cout << "Deactivated" << std::endl;
   }
   
   void onEnterFrame(std::shared_ptr<Event> e)
   {
      // Incrementing a counter to feed into cos()
      static float inc;
      inc += 0.005f;
      
      // Animate the inner bitmap to float on the y axis
      if (alienBitmap) alienBitmap->y(std::cos(inc*10.0f) * 50);
      
      if (alien) {
         // Calculate the alien velocity against the key state
         int xVel = 0;
         int yVel = 0;
         if (directions & DIRECTION_LEFT) xVel -= 1;
         if (directions & DIRECTION_RIGHT) xVel += 1;
         if (directions & DIRECTION_UP) yVel -= 1;
         if (directions & DIRECTION_DOWN) yVel += 1;
         
         // Calculate the alien position and do some simple bounds checking against the stage
         int targetX = alien->x() +  (xVel * 10.0f);
         int targetY = alien->y() + (yVel * 10.0f);
         if (targetX <= -alien->width() / 2.0f) targetX = -alien->width() / 2.0f;
         if (targetX >= (stageWidth() - alien->width() / 2.0f)) targetX = stageWidth() - (alien->width() / 2.0f);
         if (targetY <= -alien->height() / 2.0f) targetY = -alien->height() / 2.0f;
         if (targetY >= (stageHeight() - alien->height() / 2.0f)) targetY = stageHeight() - (alien->height() / 2.0f);
         alien->x(targetX);
         alien->y(targetY);
      }
   }
   
   void onKeyDown(std::shared_ptr<Event> e)
   {
      auto keyboardEvent = std::dynamic_pointer_cast<KeyboardEvent>(e);
      
      if (keyboardEvent->keyCode() == Keyboard::LEFT) {
         directions |= DIRECTION_LEFT;
      }
      else if (keyboardEvent->keyCode() == Keyboard::RIGHT) {
         directions |= DIRECTION_RIGHT;
      }
      else if (keyboardEvent->keyCode() == Keyboard::UP) {
         directions |= DIRECTION_UP;
      }
      else if (keyboardEvent->keyCode() == Keyboard::DOWN) {
         directions |= DIRECTION_DOWN;
      }
      else if (keyboardEvent->keyCode() == Keyboard::ESCAPE) {
         auto nativeApp = NativeApplication::nativeApplication();
         nativeApp->exit();
      }
      
   }
   
   void onKeyUp(std::shared_ptr<Event> e)
   {
      auto keyboardEvent = std::dynamic_pointer_cast<KeyboardEvent>(e);
      
      if (keyboardEvent->keyCode() == Keyboard::LEFT) {
         directions ^= DIRECTION_LEFT;
      }
      else if (keyboardEvent->keyCode() == Keyboard::RIGHT) {
         directions ^= DIRECTION_RIGHT;
      }
      else if (keyboardEvent->keyCode() == Keyboard::UP) {
         directions ^= DIRECTION_UP;
      }
      else if (keyboardEvent->keyCode() == Keyboard::DOWN) {
         directions ^= DIRECTION_DOWN;
      }
   }
   
protected:
   std::shared_ptr<Loader> background;
   std::shared_ptr<Loader> alien;
   std::shared_ptr<Bitmap> alienBitmap;
   
   uint32_t directions = 0;
   enum {
      DIRECTION_UP = 0x01,
      DIRECTION_DOWN = 0x02,
      DIRECTION_LEFT = 0x04,
      DIRECTION_RIGHT = 0x08
   };
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
         {"vsync", true}, // DESKTOP ONLY
         {"requestedDisplayResolution", "standard"}, // "standard" || "high"
         {"aspectRatio", "landscape"}, // MOBILE ONLY: "portrait" || "landscape" || ""
         {"autoOrients", true} // MOBILE ONLY
      }}
   };
   
   auto game = flair::make_shared<GameStage>();
   flair::run(applicationDescriptor, game);
}
