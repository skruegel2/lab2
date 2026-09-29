#include "lab2-api.h"
#include "usertraps.h"
#include "misc.h"

#include "n3_inj_proc.h"
#include "h2o_inj_proc.h"

void main (int argc, char *argv[])
{
  int n3_mol = 0;                 // Number N3 molecules
  char n3_mol_str[10];            // Passes number N3 to n3 inj process
  int h2o_mol = 0;                // Number H2O molecules
  char h2o_mol_str[10];           // Passes number H2O to h2o inj process
  sem_t n3_inj_proc;              // Completion sem for n3 inj process
  char n3_inj_proc_str[10];       // Passes sem handle to n3 inj process
  sem_t h2o_inj_proc;             // Completion sem for h2o inj process
  char h2o_inj_proc_str[10];      // Passes sem handle to h2o inj process

  if (argc != 3) {
    Printf("Usage: "); Printf(argv[0]); Printf(" <number N3 molecules, number H2O molecules>\n");
    Exit();
  }

  // Convert string from ascii command line argument to integer number
  n3_mol = dstrtol(argv[1], NULL, 10); // the "10" means base 10
  h2o_mol = dstrtol(argv[2], NULL, 10); // the "10" means base 10

  // Create semaphore to not exit this process until all other processes 
  // have signalled that they are complete.  To do this, we will initialize
  // the semaphore to (-1) * (number of signals), where "number of signals"
  // should be equal to the number of processes we're spawning - 1.  Once 
  // each of the processes has signaled, the semaphore should be back to
  // zero and the final sem_wait below will return.
  if ((n3_inj_proc = sem_create(-(n3_mol-1))) == SYNC_FAIL) {
    Printf("Bad sem_create in "); Printf(argv[0]); Printf("\n");
    Exit();
  }

  if ((h2o_inj_proc = sem_create(-(h2o_mol-1))) == SYNC_FAIL) {
    Printf("Bad sem_create in "); Printf(argv[0]); Printf("\n");
    Exit();
  }

  // Setup the command-line arguments for the new process.  We're going to
  // pass the handles to the shared memory page and the semaphore as strings
  // on the command line, so we must first convert them from ints to strings.
  ditoa(n3_inj_proc, n3_inj_proc_str);
  ditoa(n3_mol, n3_mol_str);
  ditoa(h2o_inj_proc, h2o_inj_proc_str);
  ditoa(h2o_mol, h2o_mol_str);
  
  // Now we can create the processes.  Note that you MUST end your call to
  // process_create with a NULL argument so that the operating system
  // knows how many arguments you are sending.
  process_create(N3_INJ_PROC, n3_inj_proc_str, n3_mol_str, NULL);
  process_create(H2O_INJ_PROC, h2o_inj_proc_str, h2o_mol_str, NULL);

  // And finally, wait until all spawned processes have finished.
  if (sem_wait(n3_inj_proc) != SYNC_SUCCESS) {
    Printf("Bad semaphore s_procs_completed (%d) in ", n3_inj_proc); Printf(argv[0]); Printf("\n");
    Exit();
  }
  if (sem_wait(h2o_inj_proc) != SYNC_SUCCESS) {
    Printf("Bad semaphore s_procs_completed (%d) in ", h2o_inj_proc); Printf(argv[0]); Printf("\n");
    Exit();
  }  
  Printf("All other processes completed, exiting main process.\n");
}
