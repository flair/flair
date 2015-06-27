#ifndef flair_Object_h
#define flair_Object_h

#include <memory>
#include <string>

namespace flair {

   class Object
   {
      template<typename T, typename... Ts>
      friend std::shared_ptr<T> create(Ts&&... params);

   protected:
      Object();

   public:
      virtual ~Object() = 0;


   // Methods
   public:
      virtual std::string toString() const;


   // Internal
   private:
      std::weak_ptr<Object> _instance;
   protected:
      template<typename T>
      std::shared_ptr<T> instance() const { return std::static_pointer_cast<T>(_instance.lock()); }
   };

}

#endif
