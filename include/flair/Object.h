#ifndef flair_Object_h
#define flair_Object_h

#include <memory>
#include <string>

namespace flair {
   
   class allocator;

   class Object : public std::enable_shared_from_this<Object>
   {
      friend class flair::allocator;
      
   protected:
      Object();
      
   public:
      virtual ~Object();
   
      
   // Methods
   public:
      virtual std::string toString() const;
   
      
   // Internal
   private:
      std::shared_ptr<Object> _shared;
      
   protected:
      template<class T>
      std::shared_ptr<T> shared() const
      {
         return std::const_pointer_cast<T>(std::dynamic_pointer_cast<const T>(shared_from_this()));
      }
   };
   
}

#endif
