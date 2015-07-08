includedirs { "../vendor/libuv/include", "../vendor/libuv/src" }

files {
   "../vendor/libuv/include/uv.h",
   "../vendor/libuv/include/tree.h",
   "../vendor/libuv/include/uv-errno.h",
   "../vendor/libuv/include/uv-threadpool.h",
   "../vendor/libuv/include/uv-version.h",
   "../vendor/libuv/src/fs-poll.c",
   "../vendor/libuv/src/heap-inl.h",
   "../vendor/libuv/src/inet.c",
   "../vendor/libuv/src/queue.h",
   "../vendor/libuv/src/threadpool.c",
   "../vendor/libuv/src/uv-common.c",
   "../vendor/libuv/src/uv-common.h",
   "../vendor/libuv/src/version.c"
}


filter { "action:xcode*" }
   files {
      "../vendor/libuv/include/uv-unix.h",
      "../vendor/libuv/include/uv-linux.h",
      "../vendor/libuv/include/uv-sunos.h",
      "../vendor/libuv/include/uv-darwin.h",
      "../vendor/libuv/include/uv-bsd.h",
      "../vendor/libuv/include/uv-aix.h",
      "../vendor/libuv/src/unix/async.c",
      "../vendor/libuv/src/unix/atomic-ops.h",
      "../vendor/libuv/src/unix/core.c",
      "../vendor/libuv/src/unix/dl.c",
      "../vendor/libuv/src/unix/fs.c",
      "../vendor/libuv/src/unix/getaddrinfo.c",
      "../vendor/libuv/src/unix/getnameinfo.c",
      "../vendor/libuv/src/unix/internal.h",
      "../vendor/libuv/src/unix/loop.c",
      "../vendor/libuv/src/unix/loop-watcher.c",
      "../vendor/libuv/src/unix/pipe.c",
      "../vendor/libuv/src/unix/poll.c",
      "../vendor/libuv/src/unix/process.c",
      "../vendor/libuv/src/unix/signal.c",
      "../vendor/libuv/src/unix/spinlock.h",
      "../vendor/libuv/src/unix/stream.c",
      "../vendor/libuv/src/unix/tcp.c",
      "../vendor/libuv/src/unix/thread.c",
      "../vendor/libuv/src/unix/timer.c",
      "../vendor/libuv/src/unix/tty.c",
      "../vendor/libuv/src/unix/udp.c",
      "../vendor/libuv/src/unix/proctitle.c",
      "../vendor/libuv/src/unix/darwin.c",
      "../vendor/libuv/src/unix/fsevents.c",
      "../vendor/libuv/src/unix/darwin-proctitle.c",
      "../vendor/libuv/src/unix/kqueue.c"
   }

   links { "m", "pthread" }

   defines { "_LARGEFILE_SOURCE", "_FILE_OFFSET_BITS=64", "_DARWIN_USE_64_BIT_INODE=1", "_DARWIN_UNLIMITED_SELECT=1" }


filter { "action:gmake*" }
   files {
      "../vendor/libuv/include/uv-unix.h",
      "../vendor/libuv/include/uv-linux.h",
      "../vendor/libuv/include/uv-sunos.h",
      "../vendor/libuv/include/uv-darwin.h",
      "../vendor/libuv/include/uv-bsd.h",
      "../vendor/libuv/include/uv-aix.h",
      "../vendor/libuv/src/unix/async.c",
      "../vendor/libuv/src/unix/atomic-ops.h",
      "../vendor/libuv/src/unix/core.c",
      "../vendor/libuv/src/unix/dl.c",
      "../vendor/libuv/src/unix/fs.c",
      "../vendor/libuv/src/unix/getaddrinfo.c",
      "../vendor/libuv/src/unix/getnameinfo.c",
      "../vendor/libuv/src/unix/internal.h",
      "../vendor/libuv/src/unix/loop.c",
      "../vendor/libuv/src/unix/loop-watcher.c",
      "../vendor/libuv/src/unix/pipe.c",
      "../vendor/libuv/src/unix/poll.c",
      "../vendor/libuv/src/unix/process.c",
      "../vendor/libuv/src/unix/signal.c",
      "../vendor/libuv/src/unix/spinlock.h",
      "../vendor/libuv/src/unix/stream.c",
      "../vendor/libuv/src/unix/tcp.c",
      "../vendor/libuv/src/unix/thread.c",
      "../vendor/libuv/src/unix/timer.c",
      "../vendor/libuv/src/unix/tty.c",
      "../vendor/libuv/src/unix/udp.c",
      "../vendor/libuv/src/unix/proctitle.c",
      "../vendor/libuv/src/unix/linux-core.c",
      "../vendor/libuv/src/unix/linux-inotify.c",
      "../vendor/libuv/src/unix/linux-syscalls.c",
      "../vendor/libuv/src/unix/linux-syscalls.h",

   }

   links { "m", "pthread", "dl", "rt" }

   defines { "_LARGEFILE_SOURCE", "_FILE_OFFSET_BITS=64", "_POSIX_C_SOURCE=200112" }







