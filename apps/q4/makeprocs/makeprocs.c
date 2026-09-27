#include "lab2-api.h"
#include "usertraps.h"
#include "misc.h"

#include "circular_buffer.h"

#include "n3_injection.h"
#include "h2o_injection.h"

void main (int argc, char *argv[])
{
  int n3_mol = 0;                 // Used to store number of initial n3 molecules
  int h2o_mol = 0;                // Used to store initial number of h2o molecules
  CircularBuffer *cb;             // Used to get address of shared memory page
  uint32 h_mem;                   // Used to hold handle to shared memory page
  sem_t sem_n3_inj;               // Semaphore used to wait until n3 injection complete
  char h_mem_str[10];             // Used as command-line argument to pass mem_handle to new processes
  char n3_mol_str[10];            // Used as command-line argument to pass page_mapped handle to new processes
  char h2o_mol_str[10];           // Used as command-line argument to pass page_mapped handle to new processes

  if (argc != 3) {
    Printf("Usage: "); Printf(argv[0]); Printf(" <number of processes to create>\n");
    Exit();
  }

  // Now print a message to show that everything worked
  Printf("makeprocs My PID is %d\n", Getpid());

  // Convert string from ascii command line argument to integer number
  n3_mol = dstrtol(argv[1], NULL, 10); // the "10" means base 10
  Printf("Creating %d N3 molecules\n", n3_mol);
  
  // Convert string from ascii command line argument to integer number
  h2o_mol = dstrtol(argv[2], NULL, 10); // the "10" means base 10
  Printf("Creating %d H2O molecules\n", h2o_mol);

  // Allocate space for a shared memory page, which is exactly 64KB
  // Note that it doesn't matter how much memory we actually need: we 
  // always get 64KB
  if ((h_mem = shmget()) == 0) {
    Printf("ERROR: could not allocate shared memory page in "); Printf(argv[0]);
    Printf(", exiting...\n");
    Exit();
  }

  // Map shared memory page into this process's memory space
  if ((cb = (CircularBuffer *)shmat(h_mem)) == NULL) {
    Printf("Could not map the shared page to virtual address in "); Printf(argv[0]);
    Printf(", exiting..\n");
    Exit();
  }
  // Initialize the circular buffer
  cb_init(cb);

  // Create semaphore to not exit this process until all consumers
  // have signalled that they are complete.  To do this, we will initialize
  // the semaphore to (-1) * (number of signals), where "number of signals"
  // should be equal to the number of processes we're spawning - 1.  Once 
  // each of the processes has signaled, the semaphore should be back to
  // zero and the final sem_wait below will return.

  // Create the n3 injection sem with a count of -1.  Once the n3 inj process
  // complete, the main process will not wait for it anymore
  // if ((sem_n3_inj = sem_create(-1)) == SYNC_FAIL) {
  //   Printf("Bad sem_create in "); Printf(argv[0]); Printf("\n");
  //   Exit();
  // }

  // Create semaphore to not exit this process until all producers
  // have signalled that they are complete.  To do this, we will initialize
  // the semaphore to (-1) * (number of signals), where "number of signals"
  // should be equal to the number of processes we're spawning - 1.  Once 
  // each of the processes has signaled, the semaphore should be back to
  // zero and the final sem_wait below will return.
  // if ((s_prods_completed = sem_create(-(numprocs-1))) == SYNC_FAIL) {
  //   Printf("Bad sem_create in "); Printf(argv[0]); Printf("\n");
  //   Exit();
  // }  
  // Setup the command-line arguments for the new process.  We're going to
  // pass the handles to the shared memory page and the semaphore as strings
  // on the command line, so we must first convert them from ints to strings.
  ditoa(h_mem, h_mem_str);
  ditoa(n3_mol, n3_mol_str);
  ditoa(h2o_mol, h2o_mol_str);
//  ditoa(s_cons_completed, s_cons_completed_str);

  // Now we can create the producer processes.  Note that you MUST end your call to
  // process_create with a NULL argument so that the operating system
  // knows how many arguments you are sending.
  // for(i=0; i<numprocs; i++) {
  //   process_create(PRODUCER_TO_RUN, h_mem_str, s_prods_completed_str, NULL);
  //   Printf("Process %d created\n", i*2);
  //   process_create(CONSUMER_TO_RUN, h_mem_str, s_cons_completed_str, NULL);
  //   Printf("Process %d created\n", i*2+1);
  // }

  Printf("N3 process created\n");
  process_create(N3_INJ_TO_RUN, h_mem_str, n3_mol_str, NULL);

  Printf("H2O process created\n");
  process_create(H2O_INJ_TO_RUN, h_mem_str, h2o_mol_str, NULL);

  // Wait until n3 process has stopped
  if (sem_wait(cb->sem_n3_inj) != SYNC_SUCCESS) {
    Printf("Bad semaphore sem_n3_inj.\n");
    Exit();
  }
  // Wait until h2o process has stopped
  if (sem_wait(cb->sem_h2o_inj) != SYNC_SUCCESS) {
    Printf("Bad semaphore sem_n3_inj.\n");
    Exit();
  }
  Printf("All other processes completed, exiting main process.\n");
}
