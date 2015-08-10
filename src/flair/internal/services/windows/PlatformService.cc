#include "flair/internal/services/windows/PlatformService.h"

#include <shlobj.h>
#include <shlwapi.h>
#undef ERROR

namespace flair {
namespace internal {
namespace services {
namespace windows {

   std::string PlatformService::os()
   {
      OSVERSIONINFO version;
      char operatingSystem[24] = { 0 };

      ZeroMemory(&version, sizeof(OSVERSIONINFO));
      version.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
      GetVersionEx(&version);

      _snprintf(operatingSystem, sizeof(operatingSystem), "Windows %ld.%ld", (long)version.dwMajorVersion, (long)version.dwMinorVersion);

      return operatingSystem;
   }
   
   std::string PlatformService::language()
   {
      char languageName[12];
      LANGID language = GetUserDefaultUILanguage();

      GetLocaleInfo(language, LOCALE_SISO639LANGNAME, languageName, 12);

      return languageName;
   }
   
   std::vector<std::string> PlatformService::languages()
   {
      std::vector<std::string> languageArray;
      EnumUILanguages([](LPSTR id, LONG_PTR user) -> BOOL {
         std::vector<std::string> * languageArray = (std::vector<std::string>*)user;
         
         char languageName[12];
         GetLocaleInfo((LANGID)id, LOCALE_SISO639LANGNAME, languageName, 12);
         languageArray->push_back(languageName);

         return TRUE;
      }, MUI_LANGUAGE_ID, (LONG_PTR)&languageArray);

      return languageArray;
   }
   
   std::string PlatformService::applicationDirectory()
   {
      wchar_t executablePath[1024] = { 0 };
      wchar_t * appDirectory = executablePath;

      GetModuleFileNameW(NULL, executablePath, 2048);
      PathRemoveFileSpecW(appDirectory);
      
      std::wstring result(appDirectory);

      return std::string(result.begin(), result.end());
   }
   
   std::string PlatformService::applicationStorageDirectory()
   {
      wchar_t * path;
      wchar_t * appName = nullptr;
      wchar_t executablePath[1024] = { 0 };

      SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, NULL, &path);

      GetModuleFileNameW(NULL, executablePath, 1024);
      appName = PathFindFileNameW(executablePath);
      *(PathFindExtensionW(appName)) = 0;

      std::wstring result = std::wstring(path) + L"\\" + std::wstring(appName);

      CreateDirectoryW(result.c_str(), NULL);

      CoTaskMemFree(path);

      return std::string(result.begin(), result.end());
   }
   
   std::string PlatformService::cacheDirectory()
   {
      wchar_t tempPath[1024] = { 0 };

      GetTempPathW(1024, tempPath);

      std::wstring result(tempPath);

      return std::string(result.begin(), --result.end());
   }
   
   std::string PlatformService::desktopDirectory()
   {
      wchar_t * path;

      SHGetKnownFolderPath(FOLDERID_Desktop, 0, NULL, &path);

      std::wstring result(path);

      CoTaskMemFree(path);

      return std::string(result.begin(), result.end());
   }
   
   std::string PlatformService::documentsDirectory()
   {
      wchar_t * path;

      SHGetKnownFolderPath(FOLDERID_Documents, 0, NULL, &path);

      std::wstring result(path);

      CoTaskMemFree(path);

      return std::string(result.begin(), result.end());
   }
   
   std::string PlatformService::userDirectory()
   {
      wchar_t * path;

      SHGetKnownFolderPath(FOLDERID_Profile, 0, NULL, &path);

      std::wstring result(path);

      CoTaskMemFree(path);

      return std::string(result.begin(), result.end());
   }
   
   std::string PlatformService::directorySeperator()
   {
      return "\\";
   }
   
}}}}
