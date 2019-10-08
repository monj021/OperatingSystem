/*******************************************************
 *Author: Bikram , Manjyoti , Drishika
 *Date: 5/7/2019
 *
 *This program implements reader writer problem each one
 *trying to open the same file. The race conditions are 
 *solved by semaphore, global variable, petersons algo
 *Each technique to solve is organized by a souirce file
 *named by the techniques.
 *
 *Main.c file contains the source code for creating and
 *executing the reader and writer therad.
 *
 *Function Input argument: number of reader and writer thread
 *Function Return value: sucess or failure to OS
 * *****************************************************/


#include "common.h"
int readcount;
int writecount;
int counter;
char rnum[10]="\0";
char wnum[10]="\0";



//This function initialize the file text.tx to be accessed by reader and writer.
//It creates file counter.txt to keep track of semaphore counters
//No. of reader and writer thread is input by user and threads are assigned writer and reader function 



int main()
{

    int reader_threads,writer_threads,threadcount, method_type;
    if((fp = fopen("counter.txt","w+"))==NULL){
        printf("Error opening the file\n");
        return 1;
        }
    if((fp = fopen("counter.txt","w+"))==NULL){
        printf("Error opening the file\n");
        return 1;
        }
    if((fp1 = fopen("text.txt","w+"))==NULL){
        printf("Error opening the file\n");
        return 1;
        }

    printf("Enter the no of readers: \n");
    scanf("%d",&reader_threads);
    printf("Enter the no of writers: \n");
    scanf("%d",&writer_threads);

    printf("Enter the method  type to use : \n");
    printf("\n Enter 1 for Semaphores . 2 for  Global Variables. 3 for Monitor \n");
    scanf("%d",&method_type);

    if(method_type == 1)
    {
        for(threadcount=0;threadcount<reader_threads;threadcount++)
        {
            pthread_create(&tid_reader[threadcount],NULL,reader,"reader");
        }

        for(threadcount=0;threadcount<writer_threads;threadcount++)
        {
            pthread_create(&tid_writer[threadcount],NULL,writer,"writer");
        }
    }

    else if(method_type == 2)
    {
        for(threadcount=0;threadcount<reader_threads;threadcount++)
        {
            pthread_create(&tid_reader[threadcount],NULL,reader_globalvar,"reader");
        }

        for(threadcount=0;threadcount<writer_threads;threadcount++)
        {
            pthread_create(&tid_writer[threadcount],NULL,writer_globalvar,"writer");
        }
    }
    else if(method_type == 3)
    {
        printf(" Monitor Implementation \n");
        for(threadcount=0;threadcount<reader_threads;threadcount++)
        {
            pthread_create(&tid_reader[threadcount],NULL,reader_monitor,"reader");
        }

        for(threadcount=0;threadcount<writer_threads;threadcount++)
        {
            pthread_create(&tid_writer[threadcount],NULL,writer_monitor,"writer");
        }
    }

    /*
    for(int threadcount=0;threadcount<reader_threads;threadcount++)
    {
        pthread_join(tid_reader[threadcount], &retval);
        //free(retval);
    }

    for(int threadcount=0;threadcount<writer_threads;threadcount++)
    {
        pthread_join(tid_writer[threadcount], &retval);
        //free(retval);
    }
    */

    if(method_type ==1 || method_type == 2 || method_type == 3)
    {
        printf("Created Reader Threads with ids: ");
        for(threadcount=0;threadcount<reader_threads;threadcount++)
        {
      		printf("%lu ", tid_reader[threadcount]);
        }


        printf("Created Writer Threads with ids: ");
        for(threadcount=0;threadcount<writer_threads;threadcount++)
        {
      		printf("%lu ", tid_writer[threadcount]);
        }
	printf("\n");
    }
    sleep(30);
    exit(0);

}


