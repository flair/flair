#ifndef flair_flair_h
#define flair_flair_h

#include <type_traits>
#include <string>
#include <iostream>

#include "flair/Object.h"

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

   template<typename T, typename... Ts>
   std::shared_ptr<T> create(Ts&&... params)
   {
      static_assert(std::is_base_of<Object, T>::value, "Class must inherit from flair::Object to instantiate");

      auto ptr = std::shared_ptr<T>(new T(std::forward<Ts>(params)...));
      std::static_pointer_cast<Object>(ptr)->_instance = std::weak_ptr<T>(ptr);
      return ptr;
   }

   template <typename... Args>
   void trace(const Args&... args)
   {
      TraceArgs argArray[] = {args...};
      doTrace(argArray, sizeof...(Args));
   }
}

#endif
