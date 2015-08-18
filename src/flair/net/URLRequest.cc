#include "flair/net/URLRequest.h"
#include "flair/internal/services/IPlatformService.h"

namespace flair {
namespace net {

   flair::internal::services::IPlatformService * URLRequest::platformService = nullptr;

   URLRequest::URLRequest(std::string url) : _authenticate(false), _cacheResponse(false), _contentType(""),
      _followRedirects(false), _idleTimeout(0), _manageCookies(false), _method(Method::GET), _useCache(false)
   {
      assert(platformService && "URLRequest requires IPlatformService injection");
      
      _url = url;
      _userAgent = platformService->userAgent();
   }
   
   URLRequest::~URLRequest()
   {
      
   }
   
   bool URLRequest::authenticate()
   {
      return _authenticate;
   }
   
   bool URLRequest::authenticate(bool value)
   {
      return _authenticate = value;
   }
   
   bool URLRequest::cacheResponse()
   {
      return _cacheResponse;
   }
   
   bool URLRequest::cacheResponse(bool value)
   {
      return _cacheResponse = value;
   }
   
   std::string URLRequest::contentType()
   {
      return _contentType;
   }
   
   std::string URLRequest::contentType(std::string value)
   {
      return _contentType = value;
   }
   
   JSON URLRequest::data()
   {
      return _data;
   }
   
   JSON URLRequest::data(JSON value)
   {
      return _data = value;
   }
   
   bool URLRequest::followRedirects()
   {
      return _followRedirects;
   }
   
   bool URLRequest::followRedirects(bool value)
   {
      return _followRedirects = value;
   }
   
   uint32_t URLRequest::idleTimeout()
   {
      return _idleTimeout;
   }
   
   uint32_t URLRequest::idleTimeout(uint32_t value)
   {
      return _idleTimeout = value;
   }
   
   bool URLRequest::isFilePath()
   {
      if (_url.find("file:///") || _url.find("app:/") || _url.find("app-storage:/")) return true;
          
      return false;
   }
   
   bool URLRequest::manageCookies()
   {
      return _manageCookies;
   }
   
   bool URLRequest::manageCookies(bool value)
   {
      return _manageCookies = value;
   }
   
   URLRequest::Method URLRequest::method()
   {
      return _method;
   }
   
   URLRequest::Method URLRequest::method(Method value)
   {
      return _method = value;
   }
   
   std::vector<std::string> URLRequest::requestHeaders()
   {
      return _requestHeaders;
   }
   
   std::vector<std::string> URLRequest::requestHeaders(std::vector<std::string> value)
   {
      return _requestHeaders = value;
   }
   
   std::string URLRequest::url()
   {
      return _url;
   }
   
   std::string URLRequest::url(std::string value)
   {
      return _url = value;
   }
   
   bool URLRequest::useCache()
   {
      return _useCache;
   }
   
   bool URLRequest::useCache(bool value)
   {
      return _useCache = value;
   }
   
   std::string URLRequest::userAgent()
   {
      return _userAgent;
   }
   
   std::string URLRequest::userAgent(std::string value)
   {
      return _userAgent = value;
   }
   
}}
