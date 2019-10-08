#ifndef RWGLOBAL_VARIABLE
#define RWGLOBAL_VARIABLE

#include "common.h"
int readerflag=1, writerflag=0;
pthread_mutex_t x;
pthread_t tid;
int flag[2]; 
int turn; 

#endif
