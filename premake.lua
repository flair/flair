solution "flair"
   configurations { "Debug", "Release" }
   filter { "action:xcode*" }
      xcodebuildsettings {
         ["CLANG_CXX_LANGUAGE_STANDARD"] = "c++11",
         ["CLANG_CXX_LIBRARY"] = "libc++"
      }
   filter { "action:gmake*" }
      filter "files:**.cc"
         buildoptions { "-std=c++11" }

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

   includedirs { "include", "src", "vendor/libuv/include" }

   files { "include/**.h", "src/**.h", "src/**.cc" }

   include "./build/libuv.lua"

project "tests"
   kind "ConsoleApp"
   language "C++"
   targetdir "bin/%{cfg.buildcfg}"

   includedirs { "include", "vendor/googletest/include", "vendor/googletest/" }

   files { "tests/**.cc", "vendor/googletest/src/gtest_main.cc", "vendor/googletest/src/gtest-all.cc" }

   links { "flair" }

   filter { "action:gmake*" }
      links "pthread"







