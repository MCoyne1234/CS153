#include "types.h"
#include "user.h"


int PScheduler(void);
int AgeTest(void);

int main(int argc, char *argv[])
{
  if (atoi(argv[1]) == 1){
   PScheduler();
  }
  else if (atoi(argv[1]) == 2){
    AgeTest(); 
  }else
    printf(1, "\ntype \"lab02 1\" to test the Scheduler, \"lab02 2\" to test priority age \n");
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

 //printf(1,"alive5 %d\n",getPri());
 changePriority(pid,0);
 //changePriority(0);
 //printf(1,"alive6 %d\n",getPri());

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

int AgeTest(void){
   int i;
   int pid1 = 0; 
   //int pid2 = 0;
   //int parent = getpid();
   //int status = -2;

    printf( 1, " PID START: %d PRIORITY: %d \n", getpid(), getPri());
    pid1 = fork();
   // printf(1, "FORK 1 -> PID: %d pid1 = %d pid2 = %d.\n", getpid(), pid1, pid2);
   // printf( 1, " PID START: %d PRIORITY: %d \n", getpid(), getPri());
    if( pid1 == 0 ){
        fork();
        //pid2 = fork();  
        //printf(1, "FORK 2 -> PID: %d pid1 = %d pid2 = %d.\n", getpid(), pid1, pid2);
        //printf( 1, " PID START: %d PRIORITY: %d \n", getpid(), getPri());
    }else{
      printf(1, "Pid %d will change priority to 13 (from default %d).\n", getpid(), getPri() );
      changePriority(getpid(), 13 );
      int pri = getPri();
      printf(1, "This will print when the priority has been increased:\nPriority == %d\n", pri);
      //exit(0);
    }

    if (pid1 == 0){
      for( i = 1 ; i < 193; ++i){
        //asm("nop");
        yield(); 
        if( i % 64 == 0 ){ 
          printf(1, "Pid %d has run 64 times. %d\n", getpid(), uptime()); 
          } 
      }
     //if( pid2 != 0 ) 
      //printf(1, "PID %d: Waiting for parent:\n", getpid()); 
      //waitpid(parent, &status, 0);
    }
    wait(0);
    //waitpid( 3, &status, 1 );
    //printf(1, "PID %d STATUS %d\n", getpid(), status); 
    return 0;
}
