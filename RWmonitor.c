#include "RWmonitor.h"
#include <pthread.h>

void handle_sigint(int sig)
{
    printf("Caught signal %d\n", sig);
}

void BeginWrite()
{

    // A writer can enter if there are no other
    // active writers and no readers are waiting
pthread_mutex_lock(&x);
    if (NWriters == 1 || NReaders > 0) {
	  
        ++WaitingWriters;
        
        wait(CanWrite, handle_sigint);
        --WaitingWriters;

    }

    NWriters = 1;
pthread_mutex_unlock(&x);
}

void EndWrite()
{

    pthread_mutex_lock(&x);

    NWriters = 0;
    
    // Checks to see if any readers are waiting
    if (WaitingReaders)

        signal(CanRead, handle_sigint);

    else

        signal(CanWrite, handle_sigint);
    pthread_mutex_unlock(&x);

}

void BeginRead()
{

    // A reader can enter if there are no writers
    // active or waiting, so we can have
    // many readers active all at once
    if (NWriters == 1 || WaitingWriters > 0) {

	   pthread_mutex_lock(&x);
        ++WaitingReaders;
// Otherwise, a reader waits (maybe many do)
        wait(CanRead, handle_sigint);
        --WaitingReaders;
 	   pthread_mutex_unlock(&x);
    }

    ++NReaders;
    signal(CanRead, handle_sigint);
}

void EndRead()
{

    // When a reader finishes, if it was the last reader,
    // it lets a writer in (if any is there).
    pthread_mutex_lock(&x);
    --NReaders;
    
    if (NReaders == 0)

        signal(CanWrite, handle_sigint);
     pthread_mutex_unlock(&x);
}

void *reader_monitor(void * param)
{
    int waittime;
    int count;
    waittime = rand() % 1000;
    usleep(waittime);
    printf("Reader is trying to enter\n");

    BeginRead();

   time_t start_t, end_t;
   double diff_t;

   double time_to_wait = (double)(rand()%10000);
   time(&start_t);
   printf("Reader  is inside with thread id %lu \n", pthread_self());

   while(1)
   {

    rewind(fp);
    fscanf (fp, "%d", &count);
    //fprintf(fp1,"%s read the file and the counter is %d thread id %lu\n",(char *)param,counter,pthread_self());
    //printf("File is read by %s thread %d thread id %lu\n", (char *)param, readcount, pthread_self());
   time(&end_t);
   diff_t = difftime(end_t, start_t);
 if(diff_t > (time_to_wait)/1000)
   {
      // printf("\nDifference of  time for the reader %lu   is = %f milliseconds. Break the loop\n",pthread_self(), diff_t*1000 );
       break;
   }
   else
   {
    //   printf("\nDifference of  time for the reader %lu  is = %f\n milliseconds. Time still left, continue to read\n", pthread_self(), diff_t*1000);
   }

 }

    EndRead();
    printf("Reader is Leaving with thread id %lu\n", pthread_self());
    return 0;

}

void *writer_monitor(void * param)
{
    //Prefix

    int waittime;
    waittime=rand() % 1000;
    usleep(waittime);
    printf("\nWriter is trying to enter with thread id = %lu\n", pthread_self());

    BeginWrite();

    printf("\nWriter has entered with thread id %lu\n", pthread_self());

    time_t start_t, end_t;
    double diff_t;

   double time_to_wait = (double)(rand()%10000);
   time(&start_t);
   while(1)
   {

    rewind(fp);
    //fprintf(fp, "%d", counter);
    //fprintf(fp1,"%s writes to the file and the counter is %d  thread id %lu\n",(char *)param,counter, pthread_self());
    //printf("File is written by %s thread %d thread id %lu\n", (char *)param, counter,pthread_self());

   time(&end_t);
 diff_t = difftime(end_t, start_t);
   if(diff_t > time_to_wait/1000)
   {
  //     printf("\nDifference of  time for the writer %lu  is = %f milliseconds. Break the loop\n",pthread_self(),diff_t*1000);
       break;
   }
   else
   {
//       printf("\nDifference of  time for the writer %lu is = %f milliseconds. Time still left, continue to read\n", pthread_self(), diff_t*1000);
   }
}
printf("Writer is leaving with thread id = %lu\n",pthread_self());


    EndWrite();
    //Suffix
    return 0;
}


