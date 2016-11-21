#include "types.h"
#include "user.h"

#undef NULL
#define NULL ((void*)0)

#define PGSIZE (4096)

int ppid;
int global = 0;

lock_t *lock = NULL;
#define assert(x) if (x) {} else { \
   printf(1, "%s: %d ", __FILE__, __LINE__); \
   printf(1, "assert failed (%s)\n", # x); \
   printf(1, "TEST FAILED\n"); \
   kill(ppid); \
   exit(); \
}

void worker(void *arg_ptr);

//TODO create <= 60 threads, acquire lock, print something, release lock, no overlap

int
main(int argc, char *argv[])
{
   ppid = getpid();

   lock_init(lock);

   int i;
   for (i = 0; i < 20; i++) {
     int arg = 35;
     int thread_pid = thread_create(worker, &arg);
     assert(thread_pid > 0);
   }

   //aquire lock
   
   // print
   // TODO make testable critical section
   printf(1, "Am i doing this right?");

   // release lock
   // TODO make sure there is no overlap


   for (i = 0; i < 20; i++) {
//     int thread_pid = thread_join();
//     assert(thread_pid > 0);

     thread_join();
//     assert(join_pid == thread_pid);
     //assert(global == i + 1);
   }

   //TODO close lock if possible
   
   if(global == 20)
     printf(1, "TEST PASSED\n");
   exit();
}

void
worker(void *arg_ptr) {
   lock_acquire(lock);
   int arg = *(int*)arg_ptr;
   assert(arg == 35);
//   assert(global == 1);
   global++;
   lock_release(lock);
   exit();
}

