#include "lab2-api.h"
#include "usertraps.h"
#include "misc.h"
#include "circular_buffer.h"
#include "n3_injection.h"

void main (int argc, char *argv[])
{
  uint32 h_mem;            // Handle to the shared memory page
  // sem_t sem_n3_inj;        // Semaphore to signal the original process that we're done
  CircularBuffer *cb;      // Pointer to the shared memory page
  if (argc != 3) { 
    Printf("N3 inj: Invalid number of arguments\n");
    // Printf(argv[0]);
    // Printf(" <handle_to_shared_memory_page> <handle_to_page_mapped_semaphore>\n"); 
    Exit();
  } 

  // Convert the command-line strings into integers for use as handles
  h_mem = dstrtol(argv[1], NULL, 10); // The "10" means base 10
  // sem_n3_inj = dstrtol(argv[2], NULL, 10);

  // Map shared memory page into this process's memory space
  if ((cb = (CircularBuffer *)shmat(h_mem)) == NULL) {
    Printf("Could not map the virtual address to the memory in ");
    Printf(argv[0]);
    Printf(", exiting...\n");
    Exit();
  }
 
  // Now print a message to show that everything worked
  Printf("n3 injection: My PID is %d\n", Getpid());

  // Add all source chars to buffer
  // idx = 0;
  // while (idx < sizeof(source) - 1) {
  //   sem_wait(cb->s_empty_slots);
  //   if (lock_acquire(cb->lock) != SYNC_SUCCESS) {
  //     Printf("Producer: could not acquire buffer lock\n");
  //     Exit();
  //   }
  //   Printf("producer: PID %d has the lock.\n", Getpid());

  //   cb_push(cb, source[idx]);
  //   Printf("Producer %d inserted %c\n", Getpid(), source[idx]);
  //   idx++;
  //   lock_release(cb->lock);
  //   sem_signal(cb->s_full_slots);
  // }

  // Signal the semaphore to tell the original process that we're done
  Printf("N3 inj: PID %d is complete.\n", Getpid());
  if(sem_signal(cb->sem_n3_inj) != SYNC_SUCCESS) {
    Printf("Bad semaphore sem_n3_inj ");
    Printf(argv[0]); Printf(", exiting...\n");
    Exit();
  }
}
