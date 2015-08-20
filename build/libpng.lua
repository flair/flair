includedirs { "../vendor/libpng", "../vendor/include" }

os.mkdir("../vendor/include")
os.copyfile("../vendor/libpng/scripts/pnglibconf.h.prebuilt", "../vendor/include/pnglibconf.h")

files {
   "../vendor/libpng/png.h",
   "../vendor/libpng/pngconf.h",
   "../vendor/libpng/pnglibconf.h",
   "../vendor/libpng/pngdebug.h",
   "../vendor/libpng/pnginfo.h",
   "../vendor/libpng/pngpriv.h",
   "../vendor/libpng/pngstruct.h",
   "../vendor/libpng/png.c",
   "../vendor/libpng/pngerror.c",
   "../vendor/libpng/pngget.c",
   "../vendor/libpng/pngmem.c",
   "../vendor/libpng/pngpread.c",
   "../vendor/libpng/pngread.c",
   "../vendor/libpng/pngrio.c",
   "../vendor/libpng/pngrtran.c",
   "../vendor/libpng/pngrutil.c",
   "../vendor/libpng/pngset.c",
   "../vendor/libpng/pngtrans.c",
   "../vendor/libpng/pngwio.c",
   "../vendor/libpng/pngwrite.c",
   "../vendor/libpng/pngwtran.c",
   "../vendor/libpng/pngwutil.c"
}

filter { "action:xcode*" }
   links { "m" }

filter { "action:gmake*" }
   links { "m" }

filter { "action:vs*" }
   defines { "_CRT_SECURE_NO_DEPRECATE" }

filter { }
