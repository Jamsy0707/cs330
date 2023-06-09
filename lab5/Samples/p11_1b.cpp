//
// Joining threads and interpreting exit values
//
// Based on p11.1.cxx from Interprocess Communications in Linux
// By: John Shapley Gray
// Adapted for CS330 by Alex Clarke
//

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

// Thread start
extern "C"
{
  void *say_it(void *);
}

int main(int argc, char *argv[])
{
  int num_threads;
  pthread_t *thread_ids;
  void *p_status;

  // Use unbuffered output on stdout
  setvbuf(stdout, (char *)NULL, _IONBF, 0);

  cout << "How many threads? ";
  cin >> num_threads;
  thread_ids = new pthread_t[num_threads];

  cout << "Displaying" << endl;

  // generate threads
  for (int i = 0; i < num_threads; i++)
  {
    int *arg = new int;
    *arg = i;
    if (pthread_create(&thread_ids[i], NULL, say_it, arg) > 0)
    {
      perror("creating thread:");
      return 2;
    }
    //pthread_detach(thread_ids[i]);
  }

  // join threads and print their return values
  for (int i = 0; i < num_threads; i++)
  {
    if (pthread_join(thread_ids[i], &p_status) != 0)
    {
      perror("trouble joining thread: ");
      return 3;
    }
    cout << "Thread " << i << ": " << (char *)p_status << endl;

    delete[](char *) p_status;
  }

  delete[] thread_ids;

  return 0;
}

// Build a message and return it at exit
void *say_it(void *num)
{
  int t_num = *(int *)num;
  char *msg = new char[255];
  cout << "Building message for thread" << t_num << endl;
  sleep(1);
  if (t_num == 5)
  {
    snprintf(msg, 255, "I am not %lX. I am #%d. I. AM. ALIVE.", pthread_self(),
             t_num);
    pthread_exit(msg);
  }
  snprintf(msg, 255, "My thread id was %lX. Goodbye...", pthread_self());
  return msg;
}
