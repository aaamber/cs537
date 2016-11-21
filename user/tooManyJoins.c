#include "types.h"
#include "user.h"

#undef NULL
#define NULL ((void*)0)

#define PGSIZE (4096)

int ppid;
int global = 0;

#define assert(x) if (x) {} else { \
   printf(1, "%s: %d ", __FILE__, __LINE__); \
   printf(1, "assert failed (%s)\n", # x); \
   printf(1, "TEST FAILED\n"); \
   kill(ppid); \
   exit(); \
}

// create three threads (multi) and join four times see what happens (fourth one should just skip)


void worker(void *arg_ptr);

int
main(int argc, char *argv[])
{
   ppid = getpid();

   /*int arg = 35;
   int thread_pid = thread_create(worker, &arg);
   assert(thread_pid > 0);*/

   // For each of 64 threads (max we are allowed)
   int i;
   for (i = 0; i < 3; i++) {
     int arg = 35;
     int thread_pid = thread_create(worker, &arg);
     assert(thread_pid > 0);

//     int join_pid = thread_join();
 //    assert(join_pid == thread_pid);
     //assert(global == i + 1);
   }

   for (i = 0; i < 3; i++) {
//     int arg = 35;
//     int thread_pid = thread_join();
//     assert(thread_pid > 0);

  //   thread_join();
     assert(thread_join()>0);
//     assert(join_pid == thread_pid);
     //assert(global == i + 1);
   }


     assert(thread_join() == -1);

   //fork();
   if(global == 3)
     printf(1, "TEST PASSED\n");
   exit();
}


void
worker(void *arg_ptr) {
   int arg = *(int*)arg_ptr;
   assert(arg == 35);
//   assert(global == 1);
   global++;
   exit();
}

