#include "flair/internal/services/mac/PlatformService.h"
#import <Foundation/Foundation.h>

namespace flair {
namespace internal {
namespace services {
namespace mac {
   
   std::string PlatformService::os()
   {
      char operatingSystem[24] = { 0 };
      NSOperatingSystemVersion version = [[NSProcessInfo processInfo] operatingSystemVersion];
      snprintf(operatingSystem, sizeof(operatingSystem), "Mac OS %ld.%ld", (long)version.majorVersion, (long)version.minorVersion);
      
      return operatingSystem;
   }

   std::string PlatformService::language()
   {
      NSUserDefaults * defs = [NSUserDefaults standardUserDefaults];
      NSArray * languages = [defs objectForKey:@"AppleLanguages"];
      NSString * language = [languages objectAtIndex:0];
      
      return [language UTF8String];
   }

   std::vector<std::string> PlatformService::languages()
   {
      std::vector<std::string> languageArray;
      
      NSUserDefaults * defs = [NSUserDefaults standardUserDefaults];
      NSArray * languages = [defs objectForKey:@"AppleLanguages"];
      for (unsigned long i = 0; i < [languages count]; ++i) {
         NSString * language = [languages objectAtIndex:i];
         languageArray.push_back([language UTF8String]);
      }
      
      return languageArray;
   }

   std::string PlatformService::applicationDirectory()
   {
      NSString * directoryPath = [[NSBundle mainBundle] bundlePath];
      
      const char * path = [directoryPath UTF8String];
      return path;
   }

   std::string PlatformService::applicationStorageDirectory()
   {
      NSArray * paths = NSSearchPathForDirectoriesInDomains(NSApplicationSupportDirectory, NSUserDomainMask, YES);
      NSString * directoryPath = [paths objectAtIndex:0];
      
      NSString *bundlePath = [[NSBundle mainBundle] bundlePath];
      NSString *appName = [[NSFileManager defaultManager] displayNameAtPath: bundlePath];
      
      directoryPath = [directoryPath stringByAppendingPathComponent:appName];
      
      NSFileManager *fileManager= [NSFileManager defaultManager];
      [fileManager createDirectoryAtPath:directoryPath withIntermediateDirectories:YES attributes:nil error:nil];
      
      return [directoryPath UTF8String];
   }

   std::string PlatformService::cacheDirectory()
   {
      NSArray * paths = NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES);
      NSString * directoryPath = [paths objectAtIndex:0];
      
      const char * path = [directoryPath UTF8String];
      return path;
   }

   std::string PlatformService::desktopDirectory()
   {
      NSArray * paths = NSSearchPathForDirectoriesInDomains(NSDesktopDirectory, NSUserDomainMask, YES);
      NSString * directoryPath = [paths objectAtIndex:0];
      
      const char * path = [directoryPath UTF8String];
      return path;
   }

   std::string PlatformService::documentsDirectory()
   {
      NSArray * paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
      NSString * directoryPath = [paths objectAtIndex:0];
      
      const char * path = [directoryPath UTF8String];
      return path;
   }

   std::string PlatformService::userDirectory()
   {
      return [NSHomeDirectory() UTF8String];
   }

   std::string PlatformService::directorySeperator()
   {
      return "/";
   }

}}}}
