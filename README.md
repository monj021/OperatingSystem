Project concept, problem and solutions overview:
The Project is on multithreading concept depicting reader and writer problem and the solutions provided through various synchronization technique.
The classic problem is: When multiple readers are there and multiple writers are there the data read/write may not be synchronized which will lead
to presenting wrong data to readers or corrupting data while writing.
We need to serialize the writer access so that only one writer can write the file but readers can access data.
While reades are reading multiple readers can read the data.

Project structure:
Project consists of multiple files. It is well organized and each function is well commented.
We have below files in project segregated into source files and header files:

Source files:

1. main.c( Accepts user input on number of reader, writer thread and time to sleep)
2. RWSemaphore.c (Solves the reader writer problem by using semaphore)
3. RWGlobalvariable.c (Solves the reader writer problem by using global variable)
4. RWmonitor.c (Solves the reader writer problem by using monitor)

Header files:
1. common.h (Presents all Linux standard library , global variables common to all files used in program )
2. RWSemaphore.h (Specific variables or function protos to semaphore technique is defined here)
3. RWGlobalvariable.h (Specific variables or function protos to global variable technique is defined here)
4. RWmonitor.h (Specific variables or function protos to monitor technique is defined here)

Compilation and run procedure:
1. Presented a makefile which uses Makefile parameters so that it can run on different flavors of Linux.
2. The Makefile variables CC, CFLAGS , DEPS make it flexible to adapt to any compiler on Linux platform.
3. The  program was run on Ubuntu 18.04 LTS- gcc compiler which is latest stable version released by Ubuntu and and also on windows by MinGW compiler.
4. It generates the binary Readerwriter.
5. Just extract the zip file and change directory to the extracted folder using cd command.
6. type make clean and then make command. This creates exe Readerwriter.
7. Run the exe ./Readerwriter

Project explanation:
1. When the exe is run (./Readerwriter) it asks user to enter number of reader threads, number of writer threads and method to solve the problem.
2. On user input it creates the threads and holds the thread ids in tid_reader and tid_writer.
3. based on techniques selected it goes to respective file functions and executes the reader and writer functions.

Semaphore Technique:

4. Ex: In case of semaphore method chosen, reader threads are assigned void * reader (void * param) and writers are assigned void * writer (void * param) function.
5. All readers and writers wait random time before entering critical section to depict the effect of pre-emption.
6. The read part and write part to/from the file is kept in critical section.

Readers:
7. When a reader is going to read file reader semaphore is applied.
8. When first reader is in critical section it locks  the write semaphore.// explain reason.
9. It prints the reader thread ids to keep track of which reader thread is reading and is there any preemption happened.(We expect no preemption in critical section).
10. Program is designed carefully not to add any sleep, wait in critical section otherwise it can be preempted and critical section won't be serialized.
11. After reading the file semaphore releases the reader lock.
12. We again acquire the reader semaphore to reduce the number of threads already read the file. here we check that if all threads are finished reading then release semaphore of writer to give access to writers.
13. Finally semaphore signals to release the lock for readers so that next reader can attempt to read or writer can write.
 
Writers
1. Writers are quite simpler than readers as the whole criteria to serialize them is one writer at a time.
2. It just waits and acquires the semaphore to enter to critical section to write the file.
3. It writes the files.
4. leaves critical section and signals the writer semaphore.

Global variable Technique:

1.In global variable technique we use a global common variable to make the reader and writer processes to wait and signal accordingly based on the common variable
2.This technique is not very efficient because there are chances.
3.A counter is set for the writer. If the counter value is greater than one no reader/writer can modify the file.
4. Using this global variable it is trying to wait and signal accordingly in this case.
5. But as mentioned below in this mutual exclusion is not totally guaranteed.

Monitor technique:
1. Monitor is similar to class that includes data, operations and synchronization together.
2. Monitor guarantee mutual exclusion i.e we can make one thread execute the critical section at a time.
3. When a process starts it acquires mutex at the start then operates the shared data. Temporarily it releases the lock if it is not able to finish.
4. It reacquires the lock when it start to continue and releases at the end.
5. In this case we have taken four functions BeginRead(), EndRead(),BeginWrite() and EndWrite().
6. Begin() functions check for the conditions whether there is already any writer/reader inside the critical section and perform the actions accordingly.
7. End() functions signal the global variables such that they decrement the reader/writer values after they are done with the execution.

*****************************************************************************************************************************************************************

Test Data and explanation:

Semaphore Technique
*******************
Enter the no of readers: 
2
Enter the no of writers: 
1
Enter the method  type to use : 

 Enter 1 for Semaphores . 2 for  Global Variables. 3 for Monitor 
1
Created Reader Threads with ids: 140699196073728 140699187681024 Created Writer Threads with ids: 140699179288320 
Reader is trying to enter
Reader1  is inside 

Writer is trying to enter
Reader is trying to enter
........................................................
ubuntu@ubuntu:~/reader_writers$ ./Readerwriter 
Enter the no of readers: 
1
Enter the no of writers: 
2
Enter the method  type to use : 

 Enter 1 for Semaphores . 2 for  Global Variables. 3 for Monitor 
1
Created Reader Threads with ids: 139831060498176 Created Writer Threads with ids: 139831052105472 139831043712768 

Writer is trying to enter

Writer has entered
Reader is trying to enter

Writer is trying to enter
Writer is leaving
Reader1  is inside 
Reader1  is inside 

.................................................................

Global Variable:
****************

ubuntu@ubuntu:~/reader_writers$ ./Readerwriter ././

Enter the no of readers: 
2
Enter the no of writers: 
1
Enter the method  type to use : 

 Enter 1 for Semaphores . 2 for  Global Variables. 3 for Monitor 
2
Created Reader Threads with ids: 140173142300416 140173133907712 Created Writer Threads with ids: 140173125515008 

Reader is trying to enter
Reader1  is inside 
File is read by reader thread 1

Reader is Leaving
Writer is trying to enter 
Writer has entered
File is written by writer thread 0

Writer is leaving
Reader is trying to enter
Reader1  is inside 
File is read by reader thread 1

Reader is Leaving

............................................

Monitor:

ubuntu@ubuntu:~/reader_writers$ ./Readerwriter 
Enter the no of readers: 
2
Enter the no of writers: 
1
Enter the method  type to use : 

 Enter 1 for Semaphores . 2 for  Global Variables. 3 for Monitor 
3
 Monitor Implementation 
Created Reader Threads with ids: 140512518428416 140512510035712 Created Writer Threads with ids: 140512501643008 

Writer is trying to enter
Reader is trying to enter

Writer has entered
Reader0  is inside 
Reader is trying to enter
Reader0  is inside 
Reader is Leaving
Writer is leaving
Reader is Leaving

****************************************************************************************************************************
Problems faced:


1. An accidental  mismatch of reader semaphore wait vs signal in the code costed us lot . It was in deadlock situation and hard to debug .
2. We solved that by printing thread ids and carefully reviewing the code once again.
3. Always needs to keep track of if semaphore is wait state whether corresponding signal is there or not. If different semaphores are nested then we need to check if the release of locks do not block any of the wait .
4. very difficult to estimate the thread execution sequence. So the random function and wait introduced in prefix part of thread functions preempts the threads making us hard to guess and validate the output.
5. Main Parent thread thread ID prints are always coming randomly as child threads can execute any time and pre-empt anytime.
6. We calculated the wait time in seconds whereas we have to calculate in milliseconds. It gave us unexpected results because the preemption was faster.
7. Segmentation fault was solved by using GDB and it gives a stack trace till which thread caused it. Identified the thread from gdb and fixed as param argument to writer function is not type casted to (char *) in one of the print statements 

Methods comparison:

In our opinion best method to solve the synchronization is monitor out of all 3 methods we used.

GLOBAL VARIABLES:

Global variables are not reliable way of synchronizing.
They do not provide way to define critical section and mutual exclusion.
The global variable itself is not thread safe. 
It can be modified while some other thread can try to do some operation by reading that global variable which value might be wrongly read as by the time it is read other thread have modified its value.

SEMAPHORES VS MONITORS:
1. Semaphores are low level object which provide serialization to critical section using counters.
2. Multiple threads can enter critical section depending on number of counters we use for semaphores.
3. Monitors are designed objects having members functions/variables inside the monitor which will guarantee that one thread only executes the monitor object.
4. Monitors are easy to keep track of from implementation point as they have all critical section implemented at one place.
5. semaphores are heavy weight and monitors are lightweight.
6. Monitors have flexibility of mutual exclusion + conditional signaling whereas semaphores do not have conditional signaling .
   Conditional signaling in semaphores critical section may result pre-emption.





