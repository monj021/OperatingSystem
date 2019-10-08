#include<pthread.h>
#include "RWSemaphore.h"


//Initialize the  semaphore
void intialize()
{
    pthread_mutex_init(&x,NULL);
    pthread_mutex_init(&wsem,NULL);
    readcount=0;
}


//reader function executed by thread to read count and apply semaphore for first reader
void * reader (void * param)
{
    int waittime;
    int count;
    waittime = rand() % 1000;
    usleep(waittime);
    printf("Reader is trying to enter\n");
    pthread_mutex_lock(&x);
    readcount++;
    if(readcount==1)
        pthread_mutex_lock(&wsem);

   pthread_mutex_unlock(&x);

   time_t start_t, end_t;
   double diff_t;

   printf("Reader%d  is inside \n",readcount);
   double time_to_wait = (double)(rand()%10000);
   time(&start_t);
   while(1)
   {


    rewind(fp);
    fscanf (fp, "%d", &count);
    fprintf(fp1,"%s ONE read the file and the counter is %d thread id %lu\n",(char *)param,counter,pthread_self());
fprintf(fp1,"%s TWO read the file and the counter is %d thread id %lu\n",(char *)param,counter,pthread_self());
/*
    printf("File is read by %s thread %d thread id %lu\n", (char *)param, readcount, pthread_self());*/
   time(&end_t);
   diff_t = difftime(end_t, start_t);
   if(diff_t > (time_to_wait)/1000)
                 
 {
     /*
       printf("\nDifference of  time for the reader %lu   is = %f milliseconds. Break the loop\n",pthread_self(), diff_t*1000 );
*/
       break;
   }
   else
   {
    /*
       printf("\nDifference of  time for the reader %lu  is = %f\n milliseconds. Time still left, continue to read\n", pthread_self(), diff_t*1000); */
   }

 }



    //sleep(waittime);
    pthread_mutex_lock(&x);
    readcount--;
    if(readcount==0)
        pthread_mutex_unlock(&wsem);
    pthread_mutex_unlock(&x);
    printf("Reader is Leaving\n");
    return 0;
}

// Writer function executed by writers to access the file and serialize with semaphore

void * writer (void * param)
{
    int waittime;
    waittime=rand() % 1000;
    usleep(waittime);
    printf("\nWriter is trying to enter with thread id %lu\n", pthread_self());
    pthread_mutex_lock(&wsem);
   // printf("\nWriter has entered with thread id %lu\n", pthread_self());
    counter++;
    printf("\nWriter has entered with thread id  %lu and counter %d\n", pthread_self(), counter);


    time_t start_t, end_t;
   double diff_t;

   double time_to_wait = (double)(rand()%10000);
   time(&start_t);
while(1)
   {

    rewind(fp);
    fprintf(fp, "%d", counter);
    fprintf(fp1,"%s ONE writes to the file for thread id %lu\n",(char *)param,counter, pthread_self());
fprintf(fp1,"%s TWO writes to the file for thread id %lu\n",(char *)param,counter, pthread_self());

/*
    printf("File is written by %s thread %d thread id %lu\n", (char *)param, counter,pthread_self());*/

   time(&end_t);
   diff_t = difftime(end_t, start_t);
   if(diff_t > time_to_wait/1000)
   {/*
       printf("\nDifference of  time for the writer %lu  is = %f milliseconds. Break the loop\n",pthread_self(),diff_t*1000);
*/
       break;
   }
   else
   {
/*
       printf("\nDifference of  time for the writer %lu is = %f milliseconds. Time still left, continue to read\n", pthread_self(), diff_t*1000);*/
   }
}
    pthread_mutex_unlock(&wsem);
    printf("Writer is leaving with thread id %lu\n", pthread_self());
   // exit(0);
}


