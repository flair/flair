#ifndef flair_Object_h
#define flair_Object_h

#include <memory>
#include <string>

namespace flair {
   
   class Object
   {
      template<typename U, typename... Us>
      friend std::shared_ptr<U> make_shared(Us&&... params);
      
   protected:
      Object();
      
   public:
      virtual ~Object() = 0;
      
   // Methods
   public:
      virtual std::string toString();
   
   // Internal
   protected:
      std::weak_ptr<Object> _instance;
   };
   
}

#endif
