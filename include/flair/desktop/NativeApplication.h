#ifndef flair_desktop_NativeApplication_h
#define flair_desktop_NativeApplication_h

#include "flair/JSON.h"
#include "flair/display/Stage.h"
#include "flair/events/IEventDispatcher.h"
#include "flair/events/EventDispatcher.h"

namespace flair {
   
   namespace internal {
      
      namespace services {
         class IWindowService;
         class IRenderService;
         class IKeyboardService;
         class IMouseService;
         class ITouchService;
         class IGamepadService;
         class IAsyncIOService;
         class IFileService;
      }
   }
   
   namespace desktop {
      
      enum class SystemIdleMode
      {
         KEEP_AWAKE,
         NORMAL
      };
      
      class NativeApplication : public flair::events::IEventDispatcher
      {
      public:
         static std::shared_ptr<NativeApplication> nativeApplication(flair::JSON applicationDescriptor = nullptr, std::shared_ptr<flair::display::Stage> stage = nullptr)
         {
            static std::shared_ptr<NativeApplication> instance = std::shared_ptr<NativeApplication>(new NativeApplication(applicationDescriptor, stage));
            return instance;
         }
         
         NativeApplication(NativeApplication const&) = delete;
         NativeApplication& operator=(NativeApplication const&) = delete;
         virtual ~NativeApplication();
         
      protected:
         NativeApplication(flair::JSON applicationDescriptor, std::shared_ptr<flair::display::Stage> stage);
         
      // Properties
      public:
         //std::shared_ptr<NativeWindow> activeWindow();
         
         flair::JSON applicationDescriptor();
         
         std::string applicationID();
         
         bool autoExit();
         bool autoExit(bool value);
         
         bool executeInBackground();
         bool executeInBackground(bool value);
         
         int idleThreshold();
         int idleThreshold(int value);
         
         //std::shared_ptr<NativeMenu> menu();
         //std::shared_ptr<NativeMenu> menu(std::shared_ptr<NativeMenu> value);
         
         //std::vector<std::shared_ptr<NativeWindow>> openWindows();
         
         std::string publisherID();
         
         uint32_t runtimePatchLevel();
         
         uint32_t runtimeVersion();
         
         static bool supportsMenu();
         
         SystemIdleMode systemIdleMode();
         SystemIdleMode systemIdleMode(SystemIdleMode value);
         
         int timeSinceLastUserInput();
      
         
      // Methods
      public:
         void activate(int * window = nullptr);
         
         void clear();
         
         void copy();
         
         void cut();
         
         void exit(int errorCode = 0);
         
         void paste();
         
         void selectAll();
         
         void run();
         
         
      // IEventDispatcher
      public:
         void addEventListener(std::string type, std::function<void(std::shared_ptr<flair::events::Event>)> listener, bool useCapture = false, int priority = 0) override
         {
            _stage->addEventListener(type, listener, useCapture, priority);
         }
         
         template <class T>
         void addEventListener(std::string type, void (T::*listener)(std::shared_ptr<flair::events::Event>), std::shared_ptr<T> const& instance, bool useCapture = false, int priority = 0, bool weakReference = false)
         {
            _stage->addEventListener(type, listener, instance, useCapture, priority, weakReference);
         }
         
         template <class T, typename std::enable_if<std::is_base_of<Object, T>::value>::type* = nullptr>
         void addEventListener(std::string type, void (T::*listener)(std::shared_ptr<flair::events::Event>), T* self, bool useCapture = false, int priority = 0, bool weakReference = false)
         {
            _stage->addEventListener(type, listener, self, useCapture, priority, weakReference);
         }
         
         bool dispatchEvent(std::shared_ptr<flair::events::Event> event) override
         {
            return _stage->dispatchEvent(event);
         }
         
         bool hasEventListener(std::string type) override
         {
            return _stage->hasEventListener(type);
         }
         
         void removeEventListener(std::string type, std::function<void(std::shared_ptr<flair::events::Event>)> listener, bool useCapture = false) override
         {
            _stage->removeEventListener(type, listener, useCapture);
         }
         
         bool willTrigger(std::string type) override
         {
            return _stage->willTrigger(type);
         }
         
      protected:
         bool _running;
         bool _autoExit;
         bool _executeInBackground;
         int _idleThreshold;
         SystemIdleMode _systemIdleMode;
         flair::JSON _applicationDescriptor;
         std::shared_ptr<flair::display::Stage> _stage;
         
      private:
         flair::internal::services::IWindowService * windowService;
         flair::internal::services::IRenderService * renderService;
         flair::internal::services::IKeyboardService * keyboardService;
         flair::internal::services::IMouseService * mouseService;
         flair::internal::services::ITouchService * touchService;
         flair::internal::services::IGamepadService * gamepadService;
         flair::internal::services::IAsyncIOService * asyncIOService;
         flair::internal::services::IFileService * fileService;
      };
      
   }
}

#endif
