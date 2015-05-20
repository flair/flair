#ifndef flair_flair_h
#define flair_flair_h

#include <type_traits>

#include "flair/Object.h"

namespace flair {
   
   template<typename T, typename... Ts>
   std::shared_ptr<T> make_shared(Ts&&... params)
   {
      static_assert(std::is_base_of<Object, T>::value, "Class must inherit from flair::Object to instantiate");

      auto ptr = std::shared_ptr<T>(new T(std::forward<Ts>(params)...));
      std::static_pointer_cast<Object>(ptr)->_instance = std::weak_ptr<T>(ptr);
      return ptr;
   }
}

#endif
