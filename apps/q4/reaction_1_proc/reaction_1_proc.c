#include "lab2-api.h"
#include "usertraps.h"
#include "misc.h"

#include "reaction_1_proc.h"

void main (int argc, char *argv[])
{
  sem_t reaction_1_proc;    // Semaphore to signal the original process that we're done
  sem_t sem_n3;             // Semaphore for n3 molecules
  sem_t sem_n;              // Semaphore for n molecules
  int n3_mol;               // Number N3 molecules
  int idx;                  // loop index
  if (argc != 5) { 
    Printf("Invalid # args in reaction_1_proc\n"); 
    Exit();
  } 
  // Now print a message to show that everything worked
  //Printf("reaction 1 proc: My PID is %d\n", Getpid());

  // Convert the command-line strings into integers for use as handles
  reaction_1_proc = dstrtol(argv[1], NULL, 10);
  sem_n3 = dstrtol(argv[2], NULL, 10);
  sem_n = dstrtol(argv[3], NULL, 10);
  n3_mol = dstrtol(argv[4], NULL, 10);
  

  // Signal the semaphore to tell the original process that we're done
  //Printf("h2o inj proc: PID %d is complete.\n", Getpid());
  for(idx = 0; idx < n3_mol; idx++)
  {
    sem_wait(sem_n3);
    sem_signal(sem_n);
    Printf("An N molecule is created.\n");
    sem_signal(sem_n);
    Printf("An N molecule is created.\n");
    sem_signal(sem_n);
    Printf("An N molecule is created.\n");
  }

//  Printf("Signalled reaction_1_proc\n");
  sem_signal(reaction_1_proc);

}
