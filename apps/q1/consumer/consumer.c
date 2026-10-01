#include "lab2-api.h"
#include "usertraps.h"
#include "misc.h"
#include "circular_buffer.h"
#include "consumer.h"

void main (int argc, char *argv[])
{
  uint32 h_mem;            // Handle to the shared memory page
  sem_t s_cons_completed; // Semaphore to signal the original process that we're done
  char item;
  char prev_item = '\0';
  CircularBuffer *cb;      // Pointer to the shared memory page
  const char source[] = "0123456789";
  int idx = 0;             // Index for the source string

  if (argc != 3) { 
    Printf("Consumer: Invalid number of arguments\n");
    // Printf(argv[0]);
    // Printf(" <handle_to_shared_memory_page> <handle_to_page_mapped_semaphore>\n"); 
    Exit();
  } 

  // Convert the command-line strings into integers for use as handles
  h_mem = dstrtol(argv[1], NULL, 10); // The "10" means base 10
  s_cons_completed = dstrtol(argv[2], NULL, 10);

  // Map shared memory page into this process's memory space
  if ((cb = (CircularBuffer *)shmat(h_mem)) == NULL) {
    Printf("Could not map the virtual address to the memory in ");
    Printf(argv[0]);
    Printf(", exiting...\n");
    Exit();
  }
 
  // Now print a message to show that everything worked
  //Printf("consumer: My PID is %d\n", Getpid());


  // Remove all source chars from buffer
  idx = 0;
  while (idx < sizeof(source) - 1) {
    if (lock_acquire(cb->lock) != SYNC_SUCCESS) {
      Printf("consumer: could not acquire buffer lock\n");
      Exit();
    }
    //Printf("consumer: PID %d has the lock.\n", Getpid());

    if (!cb_is_empty(cb)) {
      cb_peek(cb, &item);
      // Initial case: if prev_item is '\0', first item must be '0'
      if (prev_item == '\0' && item != '0') {
        //Printf("consumer %d Error! Expected item 0 but got %c\n", Getpid(), item);
      }
      // Out of order case
      else if (prev_item != '\0' && item != prev_item + 1) {
        //Printf("consumer %d Error! Expected item %c but got %c\n", Getpid(),  prev_item + 1, item);
      }
      // In order case
      else {
        cb_pop(cb, &item);
        Printf("Consumer %d removed %c\n", Getpid(), item);
        prev_item = item;
        idx++;
      }
    } else {
      //Printf("Buffer is empty, cannot pop\n");
    }
    lock_release(cb->lock);
  }
 
  // Signal the semaphore to tell the original process that we're done
  //Printf("consumer: PID %d is complete.\n", Getpid());
  if(sem_signal(s_cons_completed) != SYNC_SUCCESS) {
    Printf("Bad semaphore s_cons_completed (%d) in ", s_cons_completed);
    Printf(argv[0]); Printf(", exiting...\n");
    Exit();
  }
}
