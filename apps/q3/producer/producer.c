#include "lab2-api.h"
#include "usertraps.h"
#include "misc.h"
#include "circular_buffer.h"
#include "producer.h"

void main (int argc, char *argv[])
{
  uint32 h_mem;            // Handle to the shared memory page
  sem_t s_prods_completed; // Semaphore to signal the original process that we're done
  CircularBuffer *cb;      // Pointer to the shared memory page
  const char source[] = "0123456789";
  int idx = 0;             // Index for the source string
  if (argc != 3) { 
    Printf("Producer: Invalid number of arguments\n");
    // Printf(argv[0]);
    // Printf(" <handle_to_shared_memory_page> <handle_to_page_mapped_semaphore>\n"); 
    Exit();
  } 

  // Convert the command-line strings into integers for use as handles
  h_mem = dstrtol(argv[1], NULL, 10); // The "10" means base 10
  s_prods_completed = dstrtol(argv[2], NULL, 10);

  // Map shared memory page into this process's memory space
  if ((cb = (CircularBuffer *)shmat(h_mem)) == NULL) {
    Printf("Could not map the virtual address to the memory in ");
    Printf(argv[0]);
    Printf(", exiting...\n");
    Exit();
  }
 
  // Now print a message to show that everything worked
  //Printf("producer: My PID is %d\n", Getpid());

  // Add all source chars to buffer
  idx = 0;
  while (idx < sizeof(source) - 1) {
    if (lock_acquire(cb->lock) != SYNC_SUCCESS) {
      Printf("Producer: could not acquire buffer lock\n");
      Exit();
    }
    //Printf("producer: PID %d has the lock.\n", Getpid());

    while (cb_is_full(cb)){
      cond_wait(cb->not_full);
    }
    cb_push(cb, source[idx]);
    Printf("Producer %d inserted %c\n", Getpid(), source[idx]);
    idx++;

    cond_signal(cb->not_empty);
    lock_release(cb->lock);
  }

  // Signal the semaphore to tell the original process that we're done
  //Printf("producer: PID %d is complete.\n", Getpid());
  if(sem_signal(s_prods_completed) != SYNC_SUCCESS) {
    Printf("Bad semaphore s_prods_completed (%d) in ", s_prods_completed);
    Printf(argv[0]); Printf(", exiting...\n");
    Exit();
  }
}
