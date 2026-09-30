#include "lab2-api.h"
#include "usertraps.h"
#include "misc.h"

#include "n3_inj_proc.h"
#include "h2o_inj_proc.h"
#include "reaction_1_proc.h"
#include "reaction_2_proc.h"

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
  sem_t reaction_1_proc;          // Completion sem for reaction 1 process
  char reaction_1_proc_str[10];   // Passes sem handle to reaction 1 process
  sem_t sem_n3;                   // N3 mol sem
  char sem_n3_str[10];            // Passes N3 mol sem handle to reaction_1 process
  sem_t reaction_2_proc;          // Completion sem for reaction 2 process
  char reaction_2_proc_str[10];   // Passes sem handle to reaction 2 process
  sem_t sem_h2o;                  // H2O mol sem
  char sem_h2o_str[10];           // Passes H2O mol sem handle to reaction_2 process

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
    Printf("Bad sem_create n3_inj_proc");
    Exit();
  }

  if ((h2o_inj_proc = sem_create(-(h2o_mol-1))) == SYNC_FAIL) {
    Printf("Bad sem_create h2o_inj_proc");
    Exit();
  }

  if ((reaction_1_proc = sem_create(0)) == SYNC_FAIL) {
    Printf("Bad sem_create reaction_1_proc");
    Exit();
  }

  if ((sem_n3 = sem_create(0)) == SYNC_FAIL) {
    Printf("Bad sem_create sem_n3");
    Exit();
  }

  if ((reaction_2_proc = sem_create(0)) == SYNC_FAIL) {
    Printf("Bad sem_create reaction_2_proc");
    Exit();
  }

  if ((sem_h2o = sem_create(0)) == SYNC_FAIL) {
    Printf("Bad sem_create sem_h2o");
    Exit();
  }

  // Setup the command-line arguments for the new process.  We're going to
  // pass the handles to the shared memory page and the semaphore as strings
  // on the command line, so we must first convert them from ints to strings.
  ditoa(n3_inj_proc, n3_inj_proc_str);
  ditoa(n3_mol, n3_mol_str);
  ditoa(h2o_inj_proc, h2o_inj_proc_str);
  ditoa(h2o_mol, h2o_mol_str);
  ditoa(reaction_1_proc, reaction_1_proc_str);
  ditoa(sem_n3, sem_n3_str);
  ditoa(reaction_2_proc, reaction_2_proc_str);
  ditoa(sem_h2o, sem_h2o_str);

  // Now we can create the processes.  Note that you MUST end your call to
  // process_create with a NULL argument so that the operating system
  // knows how many arguments you are sending.
  process_create(N3_INJ_PROC, n3_inj_proc_str, sem_n3_str, n3_mol_str, NULL);
  process_create(H2O_INJ_PROC, h2o_inj_proc_str, sem_h2o_str, h2o_mol_str, NULL);
  process_create(REACTION_1_PROC, reaction_1_proc_str, sem_n3_str, n3_mol_str, NULL);
  Printf("reaction_2_proc %d\n", reaction_2_proc);
  Printf("sem_h2o %d\n", sem_h2o);
  Printf("h2o_mol %d\n", h2o_mol);

  process_create(REACTION_2_PROC, reaction_2_proc_str, sem_h2o_str, h2o_mol_str, NULL);

  // And finally, wait until all spawned processes have finished.
  if (sem_wait(n3_inj_proc) != SYNC_SUCCESS) {
    Printf("Bad n3_inj_proc\n");
    Exit();
  }
  Printf("n3_inj_proc ended\n");
   
  if (sem_wait(h2o_inj_proc) != SYNC_SUCCESS) {
    Printf("Bad h2o_inj_proc\n");
    Exit();
  }  
  Printf("h2o_inj_proc ended\n");
  if (sem_wait(reaction_1_proc) != SYNC_SUCCESS) {
    Printf("Bad reaction_1_proc\n");
    Exit();
  }  
  Printf("reaction_1_proc ended\n");
  if (sem_wait(reaction_2_proc) != SYNC_SUCCESS) {
    Printf("Bad reaction_2_proc\n");
    Exit();
  }  
  Printf("reaction_2_proc ended\n");

  Printf("All other processes completed, exiting main process.\n");
}
