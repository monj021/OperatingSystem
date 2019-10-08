#ifndef COMMON_HEADER
#define COMMON_HEADER

#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#include <unistd.h>

#define MAX_READER_THREAD 10
#define MAX_WRITER_THREAD 5


extern int readcount;
extern int writecount;
extern int counter;
extern char rnum[10];
extern char wnum[10];

extern pthread_t tid;
pthread_t tid_reader[MAX_READER_THREAD]; //datastructure to hold reader thread ids
pthread_t tid_writer[MAX_WRITER_THREAD]; //datastructure to hold writer thread ids
extern FILE *fp ;
extern FILE *fp1 ;
extern void * writer (void * param);
extern void * reader (void * param);
extern void *reader_globalvar(void * param);
extern void * writer_globalvar (void * param);
extern void *writer_monitor(void * param);
extern void *reader_monitor(void * param);
extern int counter;


#endif
