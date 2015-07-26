#include "flair/flair.h"
#include "flair/events/EventDispatcher.h"
#include "gtest/gtest.h"

namespace {
   using flair::events::Event;
   using flair::events::EventDispatcher;
   
   class EventDispatcherTest : public ::testing::Test
   {
   protected:
      EventDispatcherTest() {}
      virtual ~EventDispatcherTest() {}
   };
   
   TEST_F(EventDispatcherTest, Dispatch)
   {
      bool recieved = false;
      
      auto eventDispatcher = flair::make_shared<EventDispatcher>();
      eventDispatcher->addEventListener(Event::ACTIVATE, [&](std::shared_ptr<Event>) {
         recieved = true;
      });
      eventDispatcher->dispatchEvent(flair::make_shared<Event>(Event::ACTIVATE));
      
      EXPECT_TRUE(recieved);
   }
   
   TEST_F(EventDispatcherTest, Priority)
   {
      int order = 0;
      auto eventDispatcher = flair::make_shared<EventDispatcher>();
      
      eventDispatcher->addEventListener(Event::ACTIVATE, [&](std::shared_ptr<Event>) {
         EXPECT_EQ(2, ++order);
      }, false, 100);
      
      eventDispatcher->addEventListener(Event::ACTIVATE, [&](std::shared_ptr<Event>) {
         EXPECT_EQ(4, ++order);
      }, false, 0);
      
      eventDispatcher->addEventListener(Event::ACTIVATE, [&](std::shared_ptr<Event>) {
         EXPECT_EQ(6, ++order);
      }, false, -100);
      
      eventDispatcher->addEventListener(Event::ACTIVATE, [&](std::shared_ptr<Event>) {
         EXPECT_EQ(1, ++order);
      }, false, 200);
      
      eventDispatcher->addEventListener(Event::ACTIVATE, [&](std::shared_ptr<Event>) {
         EXPECT_EQ(5, ++order);
      }, false, -50);
      
      eventDispatcher->addEventListener(Event::ACTIVATE, [&](std::shared_ptr<Event>) {
         EXPECT_EQ(3, ++order);
      }, false, 50);
      
      eventDispatcher->dispatchEvent(flair::make_shared<Event>(Event::ACTIVATE));
   }
   
   TEST_F(EventDispatcherTest, AddEventListener)
   {
      int count = 0;
      
      auto eventDispatcher = flair::make_shared<EventDispatcher>();
      auto callback = [&](std::shared_ptr<Event>) { count++; };
      
      eventDispatcher->addEventListener(Event::ACTIVATE, callback, false);
      eventDispatcher->addEventListener(Event::ACTIVATE, callback, true);
      eventDispatcher->dispatchEvent(flair::make_shared<Event>(Event::ACTIVATE));
      
      EXPECT_EQ(2, count);
   }
   
   
   TEST_F(EventDispatcherTest, AddEventListenerDuplicate)
   {
      int count = 0;
      
      auto eventDispatcher = flair::make_shared<EventDispatcher>();
      auto callback = [&](std::shared_ptr<Event>) { count++; };
      
      eventDispatcher->addEventListener(Event::ACTIVATE, callback, false);
      eventDispatcher->addEventListener(Event::ACTIVATE, callback, false);
      eventDispatcher->dispatchEvent(flair::make_shared<Event>(Event::ACTIVATE));
      
      EXPECT_EQ(1, count);
   }
}

