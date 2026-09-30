#include "lab2-api.h"
#include "usertraps.h"
#include "misc.h"

#include "reaction_2_proc.h"

void main (int argc, char *argv[])
{
  sem_t reaction_2_proc;    // Semaphore to signal the original process that we're done
  sem_t sem_h2o;            // Semaphore for number of H2O molecules
  sem_t sem_o2;             // Semaphore for number of O2 molecules
  int h2o_mol;              // Number H2O molecules
  int idx;                  // loop index
  if (argc != 5) { 
    Printf("Invalid # args in reaction_2_proc\n"); 
    Exit();
  } 
  // Now print a message to show that everything worked
  //Printf("reaction 2 proc: My PID is %d\n", Getpid());

  // Convert the command-line strings into integers for use as handles
  reaction_2_proc = dstrtol(argv[1], NULL, 10);
  sem_h2o = dstrtol(argv[2], NULL, 10);
  sem_o2 = dstrtol(argv[3], NULL, 10);
  h2o_mol = dstrtol(argv[4], NULL, 10);
  
  for(idx = 0; idx < h2o_mol; idx++)
  {
    sem_wait(sem_h2o);
    // Divide by 2 since it takes 2 H2O molecules for reaction
    if ((idx % 2) == 1)
    {
      Printf("An H2 molecule is created.\n");
      Printf("An H2 molecule is created.\n");
      Printf("An O2 molecule is created.\n");
      sem_signal(sem_o2);
    }
  }

//  Printf("Signalled reaction_2_proc\n");
  sem_signal(reaction_2_proc);

}
