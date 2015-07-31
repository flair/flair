
#include "flair/internal/EventLoop.h"

#include <cstdlib>

namespace flair {
   namespace internal {

      EventLoop::EventLoop() : uv(nullptr), ready(false), quit(false), pendingOperations(128)
      {
         thread = std::thread([this]() { this->eventLoop(); });
      }

      EventLoop::~EventLoop()
      {
         quit = true;
         if (ready) uv_async_send(&asyncNullHandle);
         
         thread.join();
      }
      
      void EventLoop::enqueue()
      {
         int element = rand();
         pendingOperations.enqueue(element);

         asyncDequeueHandle.data = this;
         if (ready) uv_async_send(&asyncDequeueHandle);
      }

      void EventLoop::eventLoop()
      {
         uv = (uv_loop_t*)std::malloc(sizeof(uv_loop_t));
         uv_loop_init(uv);
         
         uv_async_init(uv, &asyncNullHandle, nullptr);
         uv_async_init(uv, &asyncDequeueHandle, EventLoop::asyncDequeue);

         ready = true;
         while (!quit) {
            uv_run(uv, UV_RUN_ONCE);
         }
         ready = false;

         uv_loop_close(uv);
         std::free(uv);
         uv = nullptr;
      }
      
      void EventLoop::asyncDequeue(uv_async_t *handle)
      {
         EventLoop *self = static_cast<EventLoop*>(handle->data);
         
         int result = 0;
         while (self->pendingOperations.try_dequeue(result)) {
            //printf("Dequeued %d\n", result);
         }
      }
   }
}
