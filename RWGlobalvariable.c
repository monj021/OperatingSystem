#include "RWGlobalvariable.h"
// This file implements the reader writer problem using global variables



//Initialize the  semaphore
void init_mutex()
{
    pthread_mutex_init(&x,NULL);
    //pthread_mutex_init(&wsem,NULL);
    readcount=0;
}

void filelock_init() 
{ 
    // Initialize lock by reseting the desire of 
    // both the threads to acquire the locks. 
    // And, giving turn to one of them. 
    flag[0] = flag[1] = 0; 
    turn = 0; 
}



void lock(int self) 
{ 
    // Set flag[self] = 1 saying you want to acquire lock 
    flag[self] = 1; 
  
    // But, first give the other thread the chance to 
    // acquire lock 
    turn = 1-self; 
  
    // Wait until the other thread looses the desire 
    // to acquire lock or it is your turn to get the lock. 
    while (flag[1-self]==1 && turn==1-self) ; 
} 

void unlock(int self) 
{ 
    // You do not desire to acquire lock in future. 
    // This will allow the other thread to acquire 
    // the lock. 
    flag[self] = 0; 
} 


//reader function executed by thread to read count and apply semaphore for first reader
void * reader_globalvar(void * param)
{
    int waittime;
    int count;
    waittime = rand() % 1000;
    usleep(waittime);
    printf("Reader is trying to enter with thread id %lu\n", pthread_self());
    pthread_mutex_lock(&x);
    readcount++;
    if(readcount==1)
        lock(readerflag);

   pthread_mutex_unlock(&x);

   time_t start_t, end_t;
   double diff_t;

   printf("Reader %d  is inside with thread id %lu\n",readcount, pthread_self());
   double time_to_wait = (double)(rand()%10000);
   time(&start_t);
   while(1)
   {
   
   
    rewind(fp);
    fscanf (fp, "%d", &count);
    fprintf(fp1,"%s ONE read the file and the counter is %d thread id %lu\n",(char *)param,counter,pthread_self());

/*
    printf("File is read by %s thread %d thread id %lu\n", (char *)param, readcount, pthread_self());*/
   time(&end_t);
   diff_t = difftime(end_t, start_t);
   if(diff_t > (time_to_wait)/1000)
   {
       break; 
   }

 }
    

    
    //sleep(waittime);
    pthread_mutex_lock(&x);
    readcount--;
    if(readcount==0)
        unlock(readerflag);
    pthread_mutex_unlock(&x);
    printf("Reader is Leaving with thread id %lu\n", pthread_self());
    return 0;
}   

// Writer function executed by writers to access the file and serialize with semaphore

void * writer_globalvar(void * param)
{
    int waittime;
    waittime=rand() % 1000;
    usleep(waittime);
    printf("\nWriter is trying to enter with thread id %lu\n", pthread_self());
    lock(writerflag);
    printf("\nWriter has entered with thread id %lu\n", pthread_self());
    counter++;

    time_t start_t, end_t;
   double diff_t;

   double time_to_wait = (double)(rand()%10000);
   time(&start_t);
   while(1)
   {

    rewind(fp);
    fprintf(fp, "%d", counter);
    fprintf(fp1,"%s ONE writes to the file for thread id %lu\n",(char *)param,counter, pthread_self());

/*
    printf("File is written by %s thread %d thread id %lu\n", (char *)param, counter,pthread_self());*/

   time(&end_t);
   diff_t = difftime(end_t, start_t);
   if(diff_t > time_to_wait/1000)
   {
       break;
   }

}
    unlock(writerflag);    
    printf("Writer is leaving with thread id %lu\n", pthread_self());
    //exit(0);
}


