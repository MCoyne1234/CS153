#include "types.h"
#include "user.h"

int exitWait(void);
int waitPid(void);

int main(int argc, char *argv[]) {
 printf(1, "####################################################\n");
 printf(1, "# This program tests the correctness of your lab#1\n");
 printf(1, "####################################################\n");
 
 if (atoi(argv[1]) == 1)
 exitWait(); // Test exit and wait
 else if (atoi(argv[1]) == 2)
 waitPid(); // Test waitpid
 // For corner cases
 // else 
  printf(1, "\ntype \"lab1 1\" to test exit and wait, \"lab1 2\" to test waitpid \n");
  
  // End of test
  exit(0);
  return 1; // Should not reach
  }
  
  
  int exitWait(void) {
    int pid, ret_pid, exit_status;
    int i;
    
    // use this part to test exit(int status) and wait(int* status)
    printf(1, "Step 1: testing exit(int status) and wait(int* status):\n");
   
    for (i = 0; i < 3; i++) {
      pid = fork();
      if (pid == 0) { // only the child executed this code
        if (i == 0) {
          printf(1, " - This is child with PID# %d and I will exit with status %d\n", getpid(), 0);
          exit(0);
        }else if (i == 1){
            printf(1, " - This is child with PID# %d and I will exit with status %d\n" ,getpid(), -1);
            exit(-1);
        }else{
            printf(1, " - This is child with PID# %d and I will exit with status %d\n" ,getpid(), 1);
            exit(1);
        } 
      } else if (pid > 0) { // only the parent exeecutes this code
        ret_pid = wait(&exit_status);
        
      printf(1, " - This is the parent: child with PID# %d has exited with status %d\n", ret_pid, exit_status);
      } else { // something went wrong with fork system call
          printf(2, " - Error using fork\n");
          exit(-1);
       }
    }
    exit_status = 0;
    printf(1, "Step 1.5: test 'wait' with no children:\n");
    pid = wait(&exit_status);
      if (pid == -1) {
         printf(1, "The process has no children.\n");
      }
    return 0;
  }
 
  int waitPid(void){ 
    
    int ret_pid, exit_status;
    int i;
    int pid_a[5]={0, 0, 0, 0, 0};
    int ret_val = 4;
    int noPID = -999;
 
// use this part to test wait(int pid, int* status, int options)
    printf(1, "Step 2: testing waitpid(int pid, int* status, int options):\n");
   
    for (i = 0; i <5; i++) {
      pid_a[i] = fork();
      
      if (pid_a[i] == 0) { // only the child executed this code 

      printf(1, " - This is the child with PID# %d and I will exit with status %d\n", getpid(), ret_val);
      exit(ret_val);
      }
    }
    
    sleep(5);
    printf(1, " - This is the parent: Now waiting for child with PID# %d\n",pid_a[3]);
    ret_pid = waitpid(pid_a[3], &exit_status, 0);
    printf(1, " - This is the parent: Child# %d has exited with status %d\n",ret_pid, exit_status);
    sleep(5);
    printf(1, " - This is the parent: Now waiting for child with PID# %d\n",pid_a[1]);
    ret_pid = waitpid(pid_a[1], &exit_status, 0);
    printf(1, " - This is the parent: Child# %d has exited with status %d\n",ret_pid, exit_status);
    sleep(5);
    printf(1, " - This is the parent: Now waiting for child with PID# %d\n",pid_a[2]);
    ret_pid = waitpid(pid_a[2], &exit_status, 0);
    printf(1, " - This is the parent: Child# %d has exited with status %d\n",ret_pid, exit_status);
    sleep(5);
    printf(1, " - This is the parent: Now waiting for child with PID# %d\n",pid_a[0]);
    ret_pid = waitpid(pid_a[0], &exit_status, 0);
    printf(1, " - This is the parent: Child# %d has exited with status %d\n",ret_pid, exit_status);
    sleep(5);
    printf(1, " - This is the parent: Now waiting for child with PID# %d\n",pid_a[4]);
    ret_pid = waitpid(getpid(), &exit_status, 0);
    printf(1, " - This is the parent trying to wait for myself. (Should print -1 next): %d. Exit status shouldn't change from above:  %d\n",ret_pid, exit_status);
 
    
    printf(1, "Step 3: testing waitpid with a pid that does not exist:\n");
    ret_pid = waitpid(noPID, &exit_status, 0);
    if(ret_pid == -1){
      printf(1, "The PID %d does not exist.\n", noPID);
     }
    else{
      printf(1, "This should never print.\n");
    }
  sleep(5);
  return 0;
  }
