#ifndef flair_JSON_h
#define flair_JSON_h

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <initializer_list>

#if _MSC_VER < 1900
	#define JSON_NOEXCEPT throw()
#else
	#define JSON_NOEXCEPT noexcept
#endif

namespace flair {

   class JSONValue;

   class JSON
   {
   public:
      // Types
      enum Type { NUL, NUMBER, BOOL, STRING, ARRAY, OBJECT };

      // Array and object typedefs
      typedef std::vector<JSON> Array;
      typedef std::map<std::string, JSON> Object;

      // Constructors for the various types of JSON value.
      JSON() JSON_NOEXCEPT;               // NUL
      JSON(std::nullptr_t) JSON_NOEXCEPT; // NUL
      JSON(double value);					// NUMBER
      JSON(int value);					// NUMBER
      JSON(bool value);					// BOOL
      JSON(const std::string &value);		// STRING
      JSON(std::string &&value);			// STRING
      JSON(const char * value);			// STRING
      JSON(const Array &values);			// ARRAY
      JSON(Array &&values);				// ARRAY
      JSON(const Object &values);			// OBJECT
      JSON(Object &&values);				// OBJECT

      // Implicit constructor: anything with a toJSON() function.
      template <class T, class = decltype(&T::toJSON)>
      JSON(const T & t) : JSON(t.toJSON()) {}

      // Implicit constructor: map-like objects (std::map, std::unordered_map, etc)
      template<class M, typename std::enable_if<
         std::is_constructible<std::string, typename M::key_type>::value &&
         std::is_constructible<JSON, typename M::mapped_type>::value,
         int>::type = 0>
      JSON(const M& m) : JSON(Object(m.begin(), m.end())) { }

      // Implicit constructor: vector-like objects (std::list, std::vector, std::set, etc)
      template<class V, typename std::enable_if<
         std::is_constructible<JSON, typename V::value_type>::value,
         int>::type = 0>
      JSON(const V& v) : JSON(Array(v.begin(), v.end())) { }

      // This prevents JSON(some_pointer) from accidentally producing a bool. Use
      // JSON(bool(some_pointer)) if that behavior is desired.
      JSON(void *) = delete;

      // Accessors
      Type type() const;

      bool isNull()   const { return type() == NUL; }
      bool isNumber() const { return type() == NUMBER; }
      bool isBool()   const { return type() == BOOL; }
      bool isString() const { return type() == STRING; }
      bool isArray()  const { return type() == ARRAY; }
      bool isObject() const { return type() == OBJECT; }

      // Return the enclosed value if this is a number, 0 otherwise. Note that JSON11 does not
      // distinguish between integer and non-integer numbers - number_value() and int_value()
      // can both be applied to a NUMBER-typed object.
      double number_value() const;
      int int_value() const;

      // Return the enclosed value if this is a boolean, false otherwise.
      bool bool_value() const;
      // Return the enclosed string if this is a string, "" otherwise.
      const std::string &string_value() const;
      // Return the enclosed std::vector if this is an array, or an empty vector otherwise.
      const Array &array_items() const;
      // Return the enclosed std::map if this is an object, or an empty map otherwise.
      const Object &object_items() const;

      // Return a reference to arr[i] if this is an array, JSON() otherwise.
      const JSON & operator[](size_t i) const;
      // Return a reference to obj[key] if this is an object, JSON() otherwise.
      const JSON & operator[](const std::string &key) const;

      // Serialize.
      static std::string stringify(const JSON &object);
      void stringify(std::string &out) const;
      std::string stringify() const
      {
         std::string out;
         stringify(out);
         return out;
      }

      // Parse. If parse fails, return JSON() and assign an error message to err.
      static JSON parse(const std::string & in, std::string & err);
      static JSON parse(const char * in, std::string & err)
      {
         if (in) {
            return parse(std::string(in), err);
         }
         else {
            err = "null input";
            return nullptr;
         }
      }
      static JSON parse(const char * in)
      {
         std::string err;
         return parse(in, err);
      }

      bool operator==(const JSON &rhs) const;
      bool operator<(const JSON &rhs) const;
      bool operator!=(const JSON &rhs) const { return !(*this == rhs); }
      bool operator<=(const JSON &rhs) const { return !(rhs < *this); }
      bool operator>(const JSON &rhs) const { return  (rhs < *this); }
      bool operator>=(const JSON &rhs) const { return !(*this < rhs); }

      /* has_shape(types, err)
      *
      * Return true if this is a JSON object and, for each item in types, has a field of
      * the given type. If not, return false and set err to a descriptive message.
      */
      typedef std::initializer_list<std::pair<std::string, Type>> shape;
      bool has_shape(const shape & types, std::string & err) const;

   private:
      std::shared_ptr<JSONValue> m_ptr;
   };
}

/* The code in this file is based on Dropbox, Inc's Json11
 * (https://github.com/dropbox/json11) and is used under the following license.
 *
 * Copyright (c) 2013 Dropbox, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#endif
