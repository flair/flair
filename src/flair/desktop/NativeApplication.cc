#include "flair/desktop/NativeApplication.h"
#include "flair/internal/EventLoop.h"

namespace flair {
   namespace desktop {
      
      using namespace flair::internal;
      
      NativeApplication::NativeApplication() : _autoExit(true), _executeInBackground(false), _idleThreshold(300), _systemIdleMode(SystemIdleMode::NORMAL)
      {
         eventLoop = new EventLoop();
      }
      
      NativeApplication::~NativeApplication()
      {
         delete eventLoop;
      }
      
      std::string NativeApplication::applicationDescriptor()
      {
         // TODO: Return JSON descriptor
         return "";
      }
      
      std::string NativeApplication::applicationID()
      {
         // TODO: Return application ID
         return "";
      }
      
      bool NativeApplication::autoExit()
      {
         return _autoExit;
      }
      
      bool NativeApplication::autoExit(bool value)
      {
         return _autoExit = value;
      }
      
      bool NativeApplication::executeInBackground()
      {
         return _executeInBackground;
      }
      
      bool NativeApplication::executeInBackground(bool value)
      {
         return _executeInBackground = value;
      }
      
      int NativeApplication::idleThreshold()
      {
         return _idleThreshold;
      }
      
      int NativeApplication::idleThreshold(int value)
      {
         return _idleThreshold = value;
      }
      
      std::string NativeApplication::publisherID()
      {
         // TODO: Return publisher ID
         return "";
      }
      
      uint32_t NativeApplication::runtimePatchLevel()
      {
         // TODO: Return runtime patch level
         return 0;
      }
      
      uint32_t NativeApplication::runtimeVersion()
      {
         // TODO: Return runtime version
         return 0;
      }
      
      bool NativeApplication::supportsMenu()
      {
         // TODO: Determine if menu is supported on this platform
         return false;
      }
      
      SystemIdleMode NativeApplication::systemIdleMode()
      {
         return _systemIdleMode;
      }
      
      SystemIdleMode NativeApplication::systemIdleMode(SystemIdleMode value)
      {
         return _systemIdleMode = value;
      }
      
      int NativeApplication::timeSinceLastUserInput()
      {
         // TODO: Return time since last update in seconds
         return 0;
      }
      
      void NativeApplication::activate(int * window)
      {
         // TODO: Activate the window
      }
      
      void NativeApplication::clear()
      {
         // TODO: Send clear command to active element
      }
      
      void NativeApplication::copy()
      {
         // TODO: Send copy command to active element
      }
      
      void NativeApplication::cut()
      {
         // TODO: Send cut command to active element
      }
      
      void NativeApplication::exit(int errorCode)
      {
         // TODO: Send exit command to active element
      }
      
      void NativeApplication::paste()
      {
         // TODO: Send paste command to active element
      }
      
      void NativeApplication::selectAll()
      {
         // TODO: Send selectAll command to active element
      }
      
   }
}
