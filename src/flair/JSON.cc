#include "flair/JSON.h"
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <limits>

#ifdef _MSC_VER
	#define snprintf(str, size, format, ...) _snprintf_s(str, size, _TRUNCATE, format, __VA_ARGS__)
#endif

namespace flair {

   class JSONValue
   {
   protected:
      friend class JSON;
      friend class JSONInt;
      friend class JSONDouble;
      virtual JSON::Type type() const = 0;
      virtual bool equals(const JSONValue * other) const = 0;
      virtual bool less(const JSONValue * other) const = 0;
      virtual void stringify(std::string &out) const = 0;
      virtual double number_value() const;
      virtual int int_value() const;
      virtual bool bool_value() const;
      virtual const std::string &string_value() const;
      virtual const JSON::Array &array_items() const;
      virtual const JSON &operator[](size_t i) const;
      virtual const JSON::Object &object_items() const;
      virtual const JSON &operator[](const std::string &key) const;
      virtual ~JSONValue() {}
   };

   namespace
   {
      using std::string;
      using std::vector;
      using std::map;
      using std::make_shared;
      using std::initializer_list;
      using std::move;

      static const int max_depth = 200;

      /* * * * * * * * * * * * * * * * * * * *
      * Serialization
      */

      static void stringify(std::nullptr_t, string &out)
      {
         out += "null";
      }

      static void stringify(double value, string &out)
      {
         char buf[32];
         snprintf(buf, sizeof buf, "%.17g", value);
         out += buf;
      }

      static void stringify(int value, string &out)
      {
         char buf[32];
         snprintf(buf, sizeof buf, "%d", value);
         out += buf;
      }

      static void stringify(bool value, string &out)
      {
         out += value ? "true" : "false";
      }

      static void stringify(const string &value, string &out)
      {
         out += '"';
         for (size_t i = 0; i < value.length(); i++) {
            const char ch = value[i];
            if (ch == '\\') {
               out += "\\\\";
            }
            else if (ch == '"') {
               out += "\\\"";
            }
            else if (ch == '\b') {
               out += "\\b";
            }
            else if (ch == '\f') {
               out += "\\f";
            }
            else if (ch == '\n') {
               out += "\\n";
            }
            else if (ch == '\r') {
               out += "\\r";
            }
            else if (ch == '\t') {
               out += "\\t";
            }
            else if (static_cast<uint8_t>(ch) <= 0x1f) {
               char buf[8];
               snprintf(buf, sizeof buf, "\\u%04x", ch);
               out += buf;
            }
            else if (static_cast<uint8_t>(ch) == 0xe2 && static_cast<uint8_t>(value[i + 1]) == 0x80
               && static_cast<uint8_t>(value[i + 2]) == 0xa8) {
               out += "\\u2028";
               i += 2;
            }
            else if (static_cast<uint8_t>(ch) == 0xe2 && static_cast<uint8_t>(value[i + 1]) == 0x80
               && static_cast<uint8_t>(value[i + 2]) == 0xa9) {
               out += "\\u2029";
               i += 2;
            }
            else {
               out += ch;
            }
         }
         out += '"';
      }

      static void stringify(const JSON::Array &values, string &out)
      {
         bool first = true;
         out += "[";
         for (const auto &value : values) {
            if (!first)
               out += ", ";
            value.stringify(out);
            first = false;
         }
         out += "]";
      }

      static void stringify(const JSON::Object &values, string &out)
      {
         bool first = true;
         out += "{";
         for (const auto &kv : values) {
            if (!first)
               out += ", ";
            stringify(kv.first, out);
            out += ": ";
            kv.second.stringify(out);
            first = false;
         }
         out += "}";
      }
   }

   std::string JSON::stringify(const JSON &object)
   {
      std::string out;
      object.m_ptr->stringify(out);
      return out;
   }

   void JSON::stringify(string &out) const
   {
      m_ptr->stringify(out);
   }

   /* * * * * * * * * * * * * * * * * * * *
   * Value wrappers
   */

   template <JSON::Type tag, typename T>
   class Value : public JSONValue
   {
   protected:
      // Constructors
      explicit Value(const T &value) : m_value(value) {}
      explicit Value(T &&value) : m_value(move(value)) {}

      // Get type tag
      JSON::Type type() const override
      {
         return tag;
      }

      // Comparisons
      bool equals(const JSONValue * other) const override
      {
         return m_value == static_cast<const Value<tag, T> *>(other)->m_value;
      }

      bool less(const JSONValue * other) const override
      {
         return m_value < static_cast<const Value<tag, T> *>(other)->m_value;
      }

      const T m_value;
      void stringify(string &out) const override { flair::stringify(m_value, out); }
   };

   class JSONDouble final : public Value<JSON::NUMBER, double>
   {
      double number_value() const override { return m_value; }
      int int_value() const override { return static_cast<int>(m_value); }
      bool equals(const JSONValue * other) const override { return m_value == other->number_value(); }
      bool less(const JSONValue * other)   const override { return m_value <  other->number_value(); }
   public:
      explicit JSONDouble(double value) : Value(value) {}
   };

   class JSONInt final : public Value<JSON::NUMBER, int>
   {
      double number_value() const override { return m_value; }
      int int_value() const override { return static_cast<int>(m_value); }
      bool equals(const JSONValue * other) const override { return m_value == other->number_value(); }
      bool less(const JSONValue * other)   const override { return m_value <  other->number_value(); }
   public:
      explicit JSONInt(int value) : Value(value) {}
   };

   class JSONBoolean final : public Value<JSON::BOOL, bool>
   {
      bool bool_value() const override { return m_value; }
   public:
      explicit JSONBoolean(bool value) : Value(value) {}
   };

   class JSONString final : public Value<JSON::STRING, string>
   {
      const string &string_value() const override { return m_value; }
   public:
      explicit JSONString(const string &value) : Value(value) {}
      explicit JSONString(string &&value) : Value(move(value)) {}
   };

   class JSONArray final : public Value<JSON::ARRAY, JSON::Array>
   {
      const JSON::Array &array_items() const override { return m_value; }
      const JSON & operator[](size_t i) const override;
   public:
      explicit JSONArray(const JSON::Array &value) : Value(value) {}
      explicit JSONArray(JSON::Array &&value) : Value(move(value)) {}
   };

   class JSONObject final : public Value<JSON::OBJECT, JSON::Object>
   {
      const JSON::Object &object_items() const override { return m_value; }
      const JSON & operator[](const string &key) const override;
   public:
      explicit JSONObject(const JSON::Object &value) : Value(value) {}
      explicit JSONObject(JSON::Object &&value) : Value(move(value)) {}
   };

   class JSONNull final : public Value<JSON::NUL, std::nullptr_t>
   {
   public:
      JSONNull() : Value(nullptr) {}
   };

   /* * * * * * * * * * * * * * * * * * * *
   * Static globals - static-init-safe
   */
   struct Statics {
      const std::shared_ptr<JSONValue> null = make_shared<JSONNull>();
      const std::shared_ptr<JSONValue> t = make_shared<JSONBoolean>(true);
      const std::shared_ptr<JSONValue> f = make_shared<JSONBoolean>(false);
      const string empty_string;
      const vector<JSON> empty_vector;
      const map<string, JSON> empty_map;
      Statics() {}
   };

   const Statics & statics()
   {
      static const Statics s{};
      return s;
   }

   const JSON & static_null()
   {
      // This has to be separate, not in Statics, because JSON() accesses statics().null.
      static const JSON JSON_null;
      return JSON_null;
   }

   /* * * * * * * * * * * * * * * * * * * *
   * Constructors
   */

   JSON::JSON() JSON_NOEXCEPT : m_ptr(statics().null) {}
   JSON::JSON(std::nullptr_t) JSON_NOEXCEPT : m_ptr(statics().null) {}
   JSON::JSON(double value) : m_ptr(make_shared<JSONDouble>(value)) {}
   JSON::JSON(int value) : m_ptr(make_shared<JSONInt>(value)) {}
   JSON::JSON(bool value) : m_ptr(value ? statics().t : statics().f) {}
   JSON::JSON(const string &value) : m_ptr(make_shared<JSONString>(value)) {}
   JSON::JSON(string &&value) : m_ptr(make_shared<JSONString>(move(value))) {}
   JSON::JSON(const char * value) : m_ptr(make_shared<JSONString>(value)) {}
   JSON::JSON(const JSON::Array &values) : m_ptr(make_shared<JSONArray>(values)) {}
   JSON::JSON(JSON::Array &&values) : m_ptr(make_shared<JSONArray>(move(values))) {}
   JSON::JSON(const JSON::Object &values) : m_ptr(make_shared<JSONObject>(values)) {}
   JSON::JSON(JSON::Object &&values) : m_ptr(make_shared<JSONObject>(move(values))) {}

   /* * * * * * * * * * * * * * * * * * * *
   * Accessors
   */

   JSON::Type JSON::type()                           const { return m_ptr->type(); }
   double JSON::number_value()                       const { return m_ptr->number_value(); }
   int JSON::int_value()                             const { return m_ptr->int_value(); }
   bool JSON::bool_value()                           const { return m_ptr->bool_value(); }
   const string & JSON::string_value()               const { return m_ptr->string_value(); }
   const vector<JSON> & JSON::array_items()          const { return m_ptr->array_items(); }
   const map<string, JSON> & JSON::object_items()    const { return m_ptr->object_items(); }
   const JSON & JSON::operator[] (size_t i)          const { return (*m_ptr)[i]; }
   const JSON & JSON::operator[] (const string &key) const { return (*m_ptr)[key]; }

   double                    JSONValue::number_value()              const { return 0; }
   int                       JSONValue::int_value()                 const { return 0; }
   bool                      JSONValue::bool_value()                const { return false; }
   const string &            JSONValue::string_value()              const { return statics().empty_string; }
   const vector<JSON> &      JSONValue::array_items()               const { return statics().empty_vector; }
   const map<string, JSON> & JSONValue::object_items()              const { return statics().empty_map; }
   const JSON &              JSONValue::operator[] (size_t)         const { return static_null(); }
   const JSON &              JSONValue::operator[] (const string &) const { return static_null(); }

   const JSON & JSONObject::operator[] (const string &key) const
   {
      auto iter = m_value.find(key);
      return (iter == m_value.end()) ? static_null() : iter->second;
   }

   const JSON & JSONArray::operator[] (size_t i) const
   {
      if (i >= m_value.size()) return static_null();
      else return m_value[i];
   }

   /* * * * * * * * * * * * * * * * * * * *
   * Comparison
   */

   bool JSON::operator== (const JSON &other) const
   {
      if (m_ptr->type() != other.m_ptr->type())
         return false;

      return m_ptr->equals(other.m_ptr.get());
   }

   bool JSON::operator< (const JSON &other) const
   {
      if (m_ptr->type() != other.m_ptr->type())
         return m_ptr->type() < other.m_ptr->type();

      return m_ptr->less(other.m_ptr.get());
   }

   namespace
   {
      /* * * * * * * * * * * * * * * * * * * *
      * Parsing
      */

      /* esc(c)
      *
      * Format char c suitable for printing in an error message.
      */
      static inline string esc(char c)
      {
         char buf[12];
         if (static_cast<uint8_t>(c) >= 0x20 && static_cast<uint8_t>(c) <= 0x7f) {
            snprintf(buf, sizeof buf, "'%c' (%d)", c, c);
         }
         else {
            snprintf(buf, sizeof buf, "(%d)", c);
         }
         return string(buf);
      }

      static inline bool in_range(long x, long lower, long upper)
      {
         return (x >= lower && x <= upper);
      }

      /* JSONParser
      *
      * Object that tracks all state of an in-progress parse.
      */
      struct JSONParser
      {
         /* State
         */
         const string &str;
         size_t i;
         string &err;
         bool failed;

         /* fail(msg, err_ret = JSON())
         *
         * Mark this parse as failed.
         */
         JSON fail(string &&msg)
         {
            return fail(move(msg), JSON());
         }

         template <typename T>
         T fail(string &&msg, const T err_ret)
         {
            if (!failed)
               err = std::move(msg);
            failed = true;
            return err_ret;
         }

         /* consume_whitespace()
         *
         * Advance until the current character is non-whitespace.
         */
         void consume_whitespace() {
            while (str[i] == ' ' || str[i] == '\r' || str[i] == '\n' || str[i] == '\t')
               i++;
         }

         /* get_next_token()
         *
         * Return the next non-whitespace character. If the end of the input is reached,
         * flag an error and return 0.
         */
         char get_next_token()
         {
            consume_whitespace();
            if (i == str.size())
               return fail("unexpected end of input", 0);

            return str[i++];
         }

         /* encode_utf8(pt, out)
         *
         * Encode pt as UTF-8 and add it to out.
         */
         void encode_utf8(long pt, string & out)
         {
            if (pt < 0)
               return;

            if (pt < 0x80) {
               out += static_cast<char>(pt);
            }
            else if (pt < 0x800) {
               out += static_cast<char>(pt >> 6) | 0xC0;
               out += static_cast<char>(pt & 0x3F) | 0x80;
            }
            else if (pt < 0x10000) {
               out += static_cast<char>(pt >> 12) | 0xE0;
               out += ((pt >> 6) & 0x3F) | 0x80;
               out += (pt & 0x3F) | 0x80;
            }
            else {
               out += static_cast<char>(pt >> 18) | 0xF0;
               out += ((pt >> 12) & 0x3F) | 0x80;
               out += ((pt >> 6) & 0x3F) | 0x80;
               out += (pt & 0x3F) | 0x80;
            }
         }

         /* parse_string()
         *
         * Parse a string, starting at the current position.
         */
         string parse_string()
         {
            string out;
            long last_escaped_codepoint = -1;
            while (true) {
               if (i == str.size())
                  return fail("unexpected end of input in string", "");

               char ch = str[i++];

               if (ch == '"') {
                  encode_utf8(last_escaped_codepoint, out);
                  return out;
               }

               if (in_range(ch, 0, 0x1f))
                  return fail("unescaped " + esc(ch) + " in string", "");

               // The usual case: non-escaped characters
               if (ch != '\\') {
                  encode_utf8(last_escaped_codepoint, out);
                  last_escaped_codepoint = -1;
                  out += ch;
                  continue;
               }

               // Handle escapes
               if (i == str.size())
                  return fail("unexpected end of input in string", "");

               ch = str[i++];

               if (ch == 'u') {
                  // Extract 4-byte escape sequence
                  string esc = str.substr(i, 4);
                  for (int j = 0; j < 4; j++) {
                     if (!in_range(esc[j], 'a', 'f') && !in_range(esc[j], 'A', 'F')
                        && !in_range(esc[j], '0', '9'))
                        return fail("bad \\u escape: " + esc, "");
                  }

                  long codepoint = strtol(esc.data(), nullptr, 16);

                  // JSON specifies that characters outside the BMP shall be encoded as a pair
                  // of 4-hex-digit \u escapes encoding their surrogate pair components. Check
                  // whether we're in the middle of such a beast: the previous codepoint was an
                  // escaped lead (high) surrogate, and this is a trail (low) surrogate.
                  if (in_range(last_escaped_codepoint, 0xD800, 0xDBFF)
                     && in_range(codepoint, 0xDC00, 0xDFFF)) {
                     // Reassemble the two surrogate pairs into one astral-plane character, per
                     // the UTF-16 algorithm.
                     encode_utf8((((last_escaped_codepoint - 0xD800) << 10)
                        | (codepoint - 0xDC00)) + 0x10000, out);
                     last_escaped_codepoint = -1;
                  }
                  else {
                     encode_utf8(last_escaped_codepoint, out);
                     last_escaped_codepoint = codepoint;
                  }

                  i += 4;
                  continue;
               }

               encode_utf8(last_escaped_codepoint, out);
               last_escaped_codepoint = -1;

               if (ch == 'b') {
                  out += '\b';
               }
               else if (ch == 'f') {
                  out += '\f';
               }
               else if (ch == 'n') {
                  out += '\n';
               }
               else if (ch == 'r') {
                  out += '\r';
               }
               else if (ch == 't') {
                  out += '\t';
               }
               else if (ch == '"' || ch == '\\' || ch == '/') {
                  out += ch;
               }
               else {
                  return fail("invalid escape character " + esc(ch), "");
               }
            }
         }

         /* parse_number()
         *
         * Parse a double.
         */
         JSON parse_number()
         {
            size_t start_pos = i;

            if (str[i] == '-')
               i++;

            // Integer part
            if (str[i] == '0') {
               i++;
               if (in_range(str[i], '0', '9'))
                  return fail("leading 0s not permitted in numbers");
            }
            else if (in_range(str[i], '1', '9')) {
               i++;
               while (in_range(str[i], '0', '9'))
                  i++;
            }
            else {
               return fail("invalid " + esc(str[i]) + " in number");
            }

            if (str[i] != '.' && str[i] != 'e' && str[i] != 'E'
               && (i - start_pos) <= static_cast<size_t>(std::numeric_limits<int>::digits10)) {
               return std::atoi(str.c_str() + start_pos);
            }

            // Decimal part
            if (str[i] == '.') {
               i++;
               if (!in_range(str[i], '0', '9'))
                  return fail("at least one digit required in fractional part");

               while (in_range(str[i], '0', '9'))
                  i++;
            }

            // Exponent part
            if (str[i] == 'e' || str[i] == 'E') {
               i++;

               if (str[i] == '+' || str[i] == '-')
                  i++;

               if (!in_range(str[i], '0', '9'))
                  return fail("at least one digit required in exponent");

               while (in_range(str[i], '0', '9'))
                  i++;
            }

            return std::strtod(str.c_str() + start_pos, nullptr);
         }

         /* expect(str, res)
         *
         * Expect that 'str' starts at the character that was just read. If it does, advance
         * the input and return res. If not, flag an error.
         */
         JSON expect(const string &expected, JSON res)
         {
            assert(i != 0);
            i--;
            if (str.compare(i, expected.length(), expected) == 0) {
               i += expected.length();
               return res;
            }
            else {
               return fail("parse error: expected " + expected + ", got " + str.substr(i, expected.length()));
            }
         }

         /* parse_JSON()
         *
         * Parse a JSON object.
         */
         JSON parse_JSON(int depth)
         {
            if (depth > max_depth) {
               return fail("exceeded maximum nesting depth");
            }

            char ch = get_next_token();
            if (failed)
               return JSON();

            if (ch == '-' || (ch >= '0' && ch <= '9')) {
               i--;
               return parse_number();
            }

            if (ch == 't')
               return expect("true", true);

            if (ch == 'f')
               return expect("false", false);

            if (ch == 'n')
               return expect("null", JSON());

            if (ch == '"')
               return parse_string();

            if (ch == '{') {
               map<string, JSON> data;
               ch = get_next_token();
               if (ch == '}')
                  return data;

               while (1) {
                  if (ch != '"')
                     return fail("expected '\"' in object, got " + esc(ch));

                  string key = parse_string();
                  if (failed)
                     return JSON();

                  ch = get_next_token();
                  if (ch != ':')
                     return fail("expected ':' in object, got " + esc(ch));

                  data[std::move(key)] = parse_JSON(depth + 1);
                  if (failed)
                     return JSON();

                  ch = get_next_token();
                  if (ch == '}')
                     break;
                  if (ch != ',')
                     return fail("expected ',' in object, got " + esc(ch));

                  ch = get_next_token();
               }
               return data;
            }

            if (ch == '[') {
               vector<JSON> data;
               ch = get_next_token();
               if (ch == ']')
                  return data;

               while (1) {
                  i--;
                  data.push_back(parse_JSON(depth + 1));
                  if (failed)
                     return JSON();

                  ch = get_next_token();
                  if (ch == ']')
                     break;
                  if (ch != ',')
                     return fail("expected ',' in list, got " + esc(ch));

                  ch = get_next_token();
                  (void)ch;
               }
               return data;
            }

            return fail("expected value, got " + esc(ch));
         }
      };
   }

   JSON JSON::parse(const string &in, string &err)
   {
      JSONParser parser{ in, 0, err, false };
      JSON result = parser.parse_JSON(0);

      // Check for any trailing garbage
      parser.consume_whitespace();
      if (parser.i != in.size())
         return parser.fail("unexpected trailing " + esc(in[parser.i]));

      return result;
   }

   /* * * * * * * * * * * * * * * * * * * *
   * Shape-checking
   */

   bool JSON::has_shape(const shape & types, string & err) const
   {
      if (!isObject()) {
         err = "expected JSON object, got " + stringify();
         return false;
      }

      for (auto & item : types) {
         if ((*this)[item.first].type() != item.second) {
            err = "bad type for " + item.first + " in " + stringify();
            return false;
         }
      }

      return true;
   }
}
         
/* The code in this file is based on Dropbox, Inc's Json11 (https://github.com/dropbox/json11) and is used under the following license.
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
