#include "lab2-api.h"
#include "usertraps.h"
#include "misc.h"

#include "reaction_3_proc.h"

void main (int argc, char *argv[])
{
  sem_t reaction_3_proc;    // Semaphore to signal the original process that we're done
  sem_t sem_n;              // Semaphore for number of n molecules
  sem_t sem_o2;             // Semaphore for number of o2 molecules
  int n_mol;                // Number n molecules
  int o2_mol;               // Number o2 molecules
  int idx;                  // loop index
  int loop_idx_max;         // Lesser of n or o2 molecules
  if (argc != 6) { 
    Printf("Invalid # args in reaction_3_proc\n"); 
    Exit();
  } 
  // Now print a message to show that everything worked
  //Printf("reaction 3 proc: My PID is %d\n", Getpid());

  // Convert the command-line strings into integers for use as handles
  reaction_3_proc = dstrtol(argv[1], NULL, 10);
  sem_n = dstrtol(argv[2], NULL, 10);
  sem_o2 = dstrtol(argv[3], NULL, 10);
  n_mol = dstrtol(argv[4], NULL, 10);
  o2_mol = dstrtol(argv[5], NULL, 10);

  // The reaction will be limited by the number of n or o2 molecules, whichever is less
  if (n_mol < o2_mol)
  {
    loop_idx_max = n_mol;
  }
  else
  {
    loop_idx_max = o2_mol;
  }
  for(idx = 0; idx < loop_idx_max; idx++)
  {
    sem_wait(sem_n);
    sem_wait(sem_o2);
    Printf("An NO2 molecule is created.\n");
  }

//  Printf("Signalled reaction_3_proc\n");
  sem_signal(reaction_3_proc);

}
