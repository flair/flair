#ifndef flair_flair_h
#define flair_flair_h

#include <cassert>
#include <cstdint>
#include <cmath>
#include <limits>
#include <type_traits>
#include <memory>
#include <functional>
#include <string>
#include <iostream>
#include <vector>
#include <map>

#include "flair/Object.h"
#include "flair/JSON.h"

namespace {
   class TraceArgs
   {
   public:
      std::string s;
      
   public:
      TraceArgs(int value) { s = std::to_string(value); }
      TraceArgs(unsigned int value) { s = std::to_string(value); }
      TraceArgs(float value) { s = std::to_string(value); }
      TraceArgs(double value) { s = std::to_string(value); }
      TraceArgs(std::string value) { s = value; }
      TraceArgs(const char* value) { s = std::string(value); }
      
      template <class T, class = flair::Object>
      TraceArgs(std::shared_ptr<T> value) { s = value->toString(); }
   };
   
   void doTrace(const TraceArgs* args, size_t num_args)
   {
      for (size_t i = 0; i < num_args; ++i) {
         std::cout << (i > 0 ? " " : "") << args[i].s;
      }
      std::cout << std::endl;
   }
}

namespace flair {

   class allocator {
   public:
      template<typename T>
      static std::shared_ptr<T> make_shared()
      {
         auto ptr = new T();
         auto sharedPtr = std::static_pointer_cast<T>(static_cast<Object*>(ptr)->_shared);
         static_cast<Object*>(ptr)->_shared.reset();
         return sharedPtr;
      };
      
      template<typename T, typename... Ts>
      static std::shared_ptr<T> make_shared(Ts... params)
      {
         auto ptr = new T(std::forward<Ts>(params)...);
         auto sharedPtr = std::static_pointer_cast<T>(static_cast<Object*>(ptr)->_shared);
         static_cast<Object*>(ptr)->_shared.reset();
         return sharedPtr;
      };
   };
   
   template<typename T, typename... Ts>
   std::shared_ptr<T> make_shared(Ts... params)
   {
      static_assert(std::is_base_of<Object, T>::value, "Class must inherit from flair::Object to instantiate");
      return allocator::make_shared<T>(std::forward<Ts>(params)...);
   }
   
   template<typename T>
   std::shared_ptr<T> make_shared()
   {
      static_assert(std::is_base_of<Object, T>::value, "Class must inherit from flair::Object to instantiate");
      return allocator::make_shared<T>();
   }
   
   template <typename... Args>
   void trace(const Args&... args)
   {
      TraceArgs argArray[] = {args...};
      doTrace(argArray, sizeof...(Args));
   }
   
   namespace display { class Stage; }
   void run(flair::JSON const& applicationDescriptor, std::shared_ptr<flair::display::Stage> stage);
}

#endif
