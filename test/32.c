#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>

int has_run[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void runMe(int *arg) {
  int value = (*arg);
  assert(value >= 0 && value < 5 && "Bad argument passed to 'runMe()!'");

  has_run[value] = 1;

  int *ret = (int*)malloc(sizeof(int));
  *ret = value * value;

  pthread_exit((void*)ret);
}

int run_threads(int n) {

    int sum = 0;

    int* args[n];
    pthread_t threads[n];

    for (int i=0; i<n; i++) {
        pthread_t thread;
        int* temp_arg = (int*)malloc(sizeof(int));
        *temp_arg = i;
        args[i] = temp_arg;
        pthread_create(&thread, NULL, (void*)&runMe, temp_arg);
        threads[i] = thread;
    }

    for (int i=0; i<n; i++) {
        int* temp = malloc(sizeof(int));
        pthread_join(threads[i], (void**)&temp);
        sum += *temp;

        free(temp);
        free(args[i]);
    }
    return sum;
}

int main (int argc, char **argv) {

  int sum = run_threads(5);

  int correct = 0;
  for(int i = 0; i < 5; ++i) {
    if(has_run[i]) correct++;
  }

  printf("%d %d", correct, sum);

  return 0;
}

