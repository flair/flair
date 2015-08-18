#ifndef flair_net_URLRequest_h
#define flair_net_URLRequest_h

#include "flair/flair.h"
#include "flair/Object.h"
#include "flair/JSON.h"

namespace flair { namespace desktop { class NativeApplication; } }
namespace flair { namespace internal { namespace services { class IPlatformService; } } }

namespace flair {
namespace net {
   
   class URLRequest : public Object
   {
      friend class flair::allocator;
      
   protected:
      URLRequest(std::string url = "");
      
   public:
      virtual ~URLRequest();
   
   // Types
      enum class Method {
         HEAD,
         GET,
         POST,
         PUT,
         DELETE,
      };
      
   // Properties
   public:
      bool authenticate();
      bool authenticate(bool value);
      
      bool cacheResponse();
      bool cacheResponse(bool value);
      
      std::string contentType();
      std::string contentType(std::string value);
      
      JSON data();
      JSON data(JSON value);
      
      bool followRedirects();
      bool followRedirects(bool value);
      
      uint32_t idleTimeout();
      uint32_t idleTimeout(uint32_t value);
      
      bool isFilePath();
      
      bool manageCookies();
      bool manageCookies(bool value);
      
      Method method();
      Method method(Method value);
      
      std::vector<std::string> requestHeaders();
      std::vector<std::string> requestHeaders(std::vector<std::string> value);
      
      std::string url();
      std::string url(std::string value);
      
      bool useCache();
      bool useCache(bool value);
      
      std::string userAgent();
      std::string userAgent(std::string value);
      
   protected:
      bool _authenticate;
      bool _cacheResponse;
      std::string _contentType;
      JSON _data;
      bool _followRedirects;
      uint32_t _idleTimeout;
      bool _manageCookies;
      Method _method;
      std::vector<std::string> _requestHeaders;
      std::string _url;
      bool _useCache;
      std::string _userAgent;
      
   // Internal
   protected:
      friend class flair::desktop::NativeApplication;
      static flair::internal::services::IPlatformService * platformService;
   };
      
}}

#endif
