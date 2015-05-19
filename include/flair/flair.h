#ifndef flair_flair_h
#define flair_flair_h

#include "flair/Object.h"

namespace flair {
   
   template<class T, typename... Ts>
   std::shared_ptr<T> make_shared(Ts&&... params)
   {
      auto ptr = std::shared_ptr<T>(new T(std::forward<Ts>(params)...));
      std::static_pointer_cast<Object>(ptr)->_instance = std::weak_ptr<T>(ptr);
      return ptr;
   }
   
}

#endif