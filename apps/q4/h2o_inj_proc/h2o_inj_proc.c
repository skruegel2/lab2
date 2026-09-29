#include "lab2-api.h"
#include "usertraps.h"
#include "misc.h"

#include "h2o_inj_proc.h"

void main (int argc, char *argv[])
{
  sem_t h2o_inj_proc;    // Semaphore to signal the original process that we're done
  int h2o_mol;           // Number N3 molecules
  int idx;              // loop index
  if (argc != 3) { 
    Printf("Usage: "); Printf(argv[0]); Printf(" <sem handle, number N3 mols>\n"); 
    Exit();
  } 
  // Now print a message to show that everything worked
  Printf("h2o inj proc: My PID is %d\n", Getpid());

  // Convert the command-line strings into integers for use as handles
  h2o_inj_proc = dstrtol(argv[1], NULL, 10);
  h2o_mol = dstrtol(argv[2], NULL, 10);
  Printf("Number of H2O  %d\n", h2o_mol);

  // Signal the semaphore to tell the original process that we're done
  //Printf("h2o inj proc: PID %d is complete.\n", Getpid());
  for(idx = 0; idx < h2o_mol; idx++)
  {
    Printf("Signalled h2o_inj_proc\n");
    sem_signal(h2o_inj_proc);  
  }

}
