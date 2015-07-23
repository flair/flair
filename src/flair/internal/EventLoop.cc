
#include "flair/internal/EventLoop.h"

#include <cstdlib>

namespace flair {
   namespace internal {

      EventLoop::EventLoop() : uv(nullptr), ready(false), quit(false), pendingOperations(128)
      {
         thread = std::thread(eventLoop, this);
      }

      EventLoop::~EventLoop()
      {
         quit = true;
         if (ready) uv_async_send(&asyncNullHandle);
         
         thread.join();
      }
      
      void EventLoop::Enqueue()
      {
         int element = rand();
         pendingOperations.enqueue(element);

         asyncDequeueHandle.data = this;
         if (ready) uv_async_send(&asyncDequeueHandle);
      }

      void EventLoop::eventLoop(EventLoop *self)
      {
         self->uv = (uv_loop_t*)std::malloc(sizeof(uv_loop_t));
         uv_loop_init(self->uv);
         
         uv_async_init(self->uv, &self->asyncNullHandle, nullptr);
         uv_async_init(self->uv, &self->asyncDequeueHandle, EventLoop::asyncDequeue);

         self->ready = true;
         while (!self->quit) {
            uv_run(self->uv, UV_RUN_ONCE);
         }
         self->ready = false;

         uv_loop_close(self->uv);
         std::free(self->uv);
         self->uv = nullptr;
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
