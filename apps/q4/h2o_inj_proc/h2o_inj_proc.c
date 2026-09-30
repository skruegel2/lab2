#include "lab2-api.h"
#include "usertraps.h"
#include "misc.h"

#include "h2o_inj_proc.h"

void main (int argc, char *argv[])
{
  sem_t h2o_inj_proc;    // Semaphore to signal the original process that we're done
  sem_t sem_h2o;         // Semaphore for number of h2o mols
  int h2o_mol;           // Number H2O molecules
  int idx;              // loop index
  if (argc != 4) { 
    Printf("Invalid # args in h2o_inj_proc\n"); 
    Exit();
  } 
  // Now print a message to show that everything worked
  Printf("h2o inj proc: My PID is %d\n", Getpid());

  // Convert the command-line strings into integers for use as handles
  h2o_inj_proc = dstrtol(argv[1], NULL, 10);
  sem_h2o = dstrtol(argv[2], NULL, 10);
  h2o_mol = dstrtol(argv[3], NULL, 10);
  Printf("H2O inj, sem_h2o %d\n", sem_h2o);
  Printf("H2O inj, h2o_mol %d\n", h2o_mol);

  Printf("Number of H2O  %d\n", h2o_mol);

  
  for(idx = 0; idx < h2o_mol; idx++)
  {
    Printf("An H2O molecule is created\n");
    sem_signal(h2o_inj_proc);  
    sem_signal(sem_h2o);
  }

}
