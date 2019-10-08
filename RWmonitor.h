#ifndef RWPETERSON_ALGO
#define RWPETERSON_ALGO

#include "common.h"

//Monitor Variables
// STATE VARIABLES
// Number of active readers; initially = 0
int NReaders = 0;

// Number of waiting readers; initially = 0
int WaitingReaders = 0;

// Number of active writers; initially = 0
int NWriters = 0;

// Number of waiting writers; initially = 0
int WaitingWriters = 0;
pthread_mutex_t x;

int* CanRead = NULL;
int* CanWrite = NULL;
pthread_mutex_t x,wsem;

#endif
