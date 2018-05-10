#include "types.h"
#include "user.h"

int main(int argc, char *argv[])
{
   //printf("alive1");
   int PScheduler(void);
   //printf("alive2");
   PScheduler();
   //printf("alive3");
   // End of test
    exit(0);
}   
int PScheduler(void)
{ 	
 //printf("alive4");
             		 
// use this part to test the priority scheduler.
// Assuming that the priorities range between range between 0 to 63
// 0 is the highest priority. All processes have a default priority of 20 
 int pid, ret_pid, exit_status;
 int mypid;
 int i,j,k;
 	             		               
printf(1, "\n  Step 2: testing the priority scheduler and changePriority(int pid,int priority) systema call:\n");
 printf(1, "\n  Step 2: Assuming that the priorities range between range between 0 to 63\n");
 printf(1, "\n  Step 2: 0 is the highest priority. All processes have a default priority of 10\n");
 printf(1, "\n  Step 2: The parent processes will switch to priority 0\n");
 //setPriority(0);
 pid=getpid();

 printf(1,"alive5 %d\n",getPri());
 changePriority(pid,0);
 //changePriority(0);
 printf(1,"alive6 %d\n",getPri());

 for (i = 0; i <  3; i++)
 {
  pid = fork();
  if (pid > 0 ) //parent forks twice
    continue;
  else if ( pid == 0) 
  {
   printf(1, "\n Hello! this is child# %d and I will change my priority to %d \n",getpid(),60-10*i);
  // setPriority(30-10*i);
   mypid=getpid();
   changePriority(mypid,60-10*i);
   //changePriority(60-10*i);
   //printf(1,"PRIORITY CHANGED %d\n",getPri());
   
   for (j=0;j<50000;j++)
   {	
    for(k=0;k<10000;k++) 
    { 
      asm("nop"); 
    }
   }
   printf(1, "\n child# %d with priority %d has finished! \n",getpid(),60-10*i);
   exit(0);
  }
  else
  {
   printf(2," \n Error \n");
   exit(-1);
  }
 } 
 if(pid > 0)
 {
   for (i = 0; i <  3; i++) 
   {
     ret_pid = wait(&exit_status);
     printf(1,"\n This is the parent: child with PID# %d has finished with status %d \n",ret_pid,exit_status);
   }
   printf(1,"\n if processes with highest priority finished first then its correct \n");
 }
return 0;
}
