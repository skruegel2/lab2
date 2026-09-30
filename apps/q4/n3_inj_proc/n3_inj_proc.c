#include "lab2-api.h"
#include "usertraps.h"
#include "misc.h"

#include "n3_inj_proc.h"

void main (int argc, char *argv[])
{
  sem_t n3_inj_proc;    // Semaphore to signal the original process that we're done
  sem_t sem_n3;         // Semaphore to signal reaction 1 process 
  int n3_mol;           // Number N3 molecules
  int idx;              // loop index
  if (argc != 4) { 
    Printf("Invalid args in n3_inj_proc\n"); 
    Exit();
  } 
  // Now print a message to show that everything worked
  Printf("n3 inj proc: My PID is %d\n", Getpid());

  // Convert the command-line strings into integers for use as handles
  n3_inj_proc = dstrtol(argv[1], NULL, 10);
  sem_n3 = dstrtol(argv[2], NULL, 10);
  n3_mol = dstrtol(argv[3], NULL, 10);
  Printf("Number of N3  %d\n", n3_mol);

  // Signal the semaphore to tell the original process that we're done
 // Printf("n3 inj proc: PID %d is complete.\n", Getpid());
  for(idx = 0; idx < n3_mol; idx++)
  {
    Printf("An N3 molecule is created\n");
    sem_signal(n3_inj_proc);  
    sem_signal(sem_n3);
  }

}
