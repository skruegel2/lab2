#include "lab2-api.h"
#include "usertraps.h"
#include "misc.h"

#include "consumer.h"

void main (int argc, char *argv[])
{
  uint32 h_mem;            // Handle to the shared memory page
  sem_t s_cons_completed; // Semaphore to signal the original process that we're done

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
  // if ((mc = (missile_code *)shmat(h_mem)) == NULL) {
  //   Printf("Could not map the virtual address to the memory in "); Printf(argv[0]); Printf(", exiting...\n");
  //   Exit();
  // }
 
  // Now print a message to show that everything worked
  Printf("consumer: This is one of the consumer instances you created.\n");
  Printf("consumer: My PID is %d\n", Getpid());

  // Signal the semaphore to tell the original process that we're done
  Printf("consumer: PID %d is complete.\n", Getpid());
  if(sem_signal(s_cons_completed) != SYNC_SUCCESS) {
    Printf("Bad semaphore s_cons_completed (%d) in ", s_cons_completed);
    Printf(argv[0]); Printf(", exiting...\n");
    Exit();
  }
}
