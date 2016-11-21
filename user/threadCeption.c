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

// create a thread within a thread and join them
// TODO figure out how and when to pass
// Need to delete assert?

void routine (void * argument)
{
  /* divide */
  int tmp1 = *(int*)argument/2;
  int tmp2 = *(int*)argument * 2;
  void * left_arg = &tmp1;
  void * right_arg = &tmp2;

  /* conquor */
  thread_create (routine, left_arg);
  thread_create (routine, right_arg);

  /* wait for 'children' */
  assert(thread_join()>0);
  assert(thread_join()>0);

  /* merge results & return */
}


int
main(int argc, char *argv[])
{
   ppid = getpid();
   int arg = 35;
   int thread_pid = thread_create(routine, &arg);
   assert(thread_pid > 0);
   printf(1, "TEST PASSED\n");
   exit();
}
