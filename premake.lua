newoption {
   trigger     = "platform",
   value       = "native",
   description = "Set the target platform. i.e. You may be generating MSVC solutions for andriod, or an Xcode solutions for iOS",
   allowed = {
      { "native",  "Target the Windows, Mac, Linux system you are currently on" },
      { "iOS",     "Target iOS when generating Xcode projects" },
      { "android", "Target andorid when generating msvc or gmake solutions" },
      { "mock",    "Mock platform used for testing or as a backend" }
   }
}

newoption {
   trigger     = "renderer",
   value       = "SDL",
   description = "Set the rendering backend",
   allowed = {
      { "SDL",      "SDL is the default backend, may be replaced later" },
      { "OpenGLES", "Use OpenGLES on supported platforms and angle to polyfill on dekstop platforms" },
   }
}

newoption {
   trigger     = "io",
   value       = "uv",
   description = "Set the io service for file and network requests",
   allowed = {
      { "uv",         "Use libuv for all async IO requests" },
      { "emscripten", "Emscripten IO" },
   }
}

if (not _OPTIONS["platform"]) then _OPTIONS["platform"] = "native" end
if (not _OPTIONS["renderer"]) then _OPTIONS["renderer"] = "SDL" end
if (not _OPTIONS["io"]) then _OPTIONS["io"] = "uv" end

solution "flair"
   configurations { "Debug", "Release" }

   -- Set our platform defines
   if (_OPTIONS["platform"] ~= "mock") then
     defines { "FLAIR_PLATFORM_SDL" }
   else
     defines { "FLAIR_PLATFORM_MOCK" }
   end

   if (_OPTIONS["platform"] == "native") then
     filter { "action:xcode*" }
      defines { "FLAIR_PLATFORM_MAC" }
     filter { "action:vs*" }
      defines { "FLAIR_PLATFORM_WINDOWS" }
     filter { "action:gmake*" }
       defines { "FLAIR_PLATFORM_LINUX" }
     filter { }
   end


   -- Set our renderer defines
   defines { "FLAIR_RENDERER_" .. string.upper(_OPTIONS["renderer"]); }

   -- Set our io
   defines { "FLAIR_IO_" .. string.upper(_OPTIONS["io"]); }

   filter { "action:xcode*" }
      xcodebuildsettings {
         ["CLANG_CXX_LANGUAGE_STANDARD"] = "c++11",
         ["CLANG_CXX_LIBRARY"] = "libc++"
      }

   filter { "action:gmake*" }
      flags { "C++11" }

   filter "configurations:Debug"
      defines { "DEBUG" }
      flags { "Symbols" }

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"

project "flair"
   kind "StaticLib"
   language "C++"
   targetdir "bin/%{cfg.buildcfg}"

   includedirs { "include", "src" }

   files { "include/**.h", "src/**.h", "src/**.cc" }

   include "./build/libuv.lua"

   include "./build/libsdl.lua"

project "tests"
   kind "ConsoleApp"
   language "C++"
   targetdir "bin/%{cfg.buildcfg}"

   includedirs { "include", "vendor/googletest/include", "vendor/googletest/" }

   files { "tests/**.cc", "vendor/googletest/src/gtest_main.cc", "vendor/googletest/src/gtest-all.cc" }

   links { "flair" }

   filter { "action:gmake*" }
      links { "dl", "m", "rt", "pthread" }

   filter { "action:vs*" }
      links { "imm32", "oleaut32", "winmm", "version" }

project "reference"
   kind "WindowedApp"
   language "C++"
   targetdir "bin/%{cfg.buildcfg}"

   includedirs { "include" }

   files { "reference/**.cc" }

   links { "flair" }

   filter { "action:xcode*" }
      links {
         "CoreVideo.framework",
         "AudioToolbox.framework",
         "AudioUnit.framework",
         "Cocoa.framework",
         "CoreAudio.framework",
         "IOKit.framework",
         "Carbon.framework",
         "ForceFeedback.framework",
         "CoreFoundation.framework"
      }

   filter { "action:gmake*" }
      links { "dl", "m", "rt", "pthread" }

   filter { "action:vs*" }
      links { "imm32", "oleaut32", "winmm", "version", "advapi32", "iphlpapi", "psapi", "shell32", "userenv", "ws2_32" }
