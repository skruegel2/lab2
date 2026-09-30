#include "lab2-api.h"
#include "usertraps.h"
#include "misc.h"

#include "reaction_2_proc.h"

void main (int argc, char *argv[])
{
  sem_t reaction_2_proc;    // Semaphore to signal the original process that we're done
  sem_t sem_h2o;            // Semaphore for number of H2O molecules
  int h2o_mol;               // Number N3 molecules
  int idx;                  // loop index
  if (argc != 4) { 
    Printf("Invalid # args in reaction_2_proc\n"); 
    Exit();
  } 
  // Now print a message to show that everything worked
  Printf("reaction 2 proc: My PID is %d\n", Getpid());

  // Convert the command-line strings into integers for use as handles
  reaction_2_proc = dstrtol(argv[1], NULL, 10);
  sem_h2o = dstrtol(argv[2], NULL, 10);
  h2o_mol = dstrtol(argv[3], NULL, 10);
  Printf("reaction_2_proc %d\n", reaction_2_proc);
  Printf("sem_h2o %d\n", sem_h2o);
  Printf("h2o_mol %d\n", h2o_mol);
  Printf("reaction 2 proc: h2o_mol =  %d\n", h2o_mol);
  
  for(idx = 0; idx < h2o_mol; idx++)
  {
    sem_wait(sem_h2o);
    Printf("Signalled 2H2\n");
    Printf("Signalled O2\n");
  }

  Printf("Signalled reaction_2_proc\n");
  sem_signal(reaction_2_proc);

}
