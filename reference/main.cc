#include "flair/flair.h"
#include "flair/events/Event.h"
#include "flair/events/KeyboardEvent.h"
#include "flair/display/Stage.h"

using flair::events::Event;
using flair::events::KeyboardEvent;
using flair::display::Stage;


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
   
public:
   void onActivated(std::shared_ptr<Event> e)
   {
      std::cout << "Activated" << std::endl;
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
      std::cout << "On Key Down: " << keyboardEvent->keyCode() << "with shift: " << keyboardEvent->shiftKey() << std::endl;
      
   }
};

int main(int argc, const char* argv[])
{
   auto game = flair::make_shared<GameStage>();
   flair::run(game, 1280, 720, false);
}
