/***********************************************************************
 * We shall speak for the law and the land as we drive the mongrel dogs
 * of the Empire for Morrowind
 *
 * Come Moon-And-Star, come to me through Fire and War.
 *
 * You n'wah
 * S'wit
 * Die fetcher!
 *
 * Muatra is a perfectly good piece of lore
 *
 * The Shonni-Etta Excerpts are perfectly valida nd canon
 *
 **********************************************************************/

#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>

int has_run[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void runMe(int *arg) {

  int value = (*arg);
  printf("%d ", value);
  assert(value >= 0 && value < 5 && "Bad argument passed to 'runMe()!'");

  has_run[value] = 1;

  int *ret = (int*)malloc(sizeof(int));
  *ret = value * value;

  pthread_exit((void*)ret);
}

int run_threads(int n) {
    int sumExitCodes;

    pthread_t threads[n];
    int* nums[n];

    for (int i=0; i<=(n-1); i++) {
        pthread_t thread;

        int *num = (int*)malloc(sizeof(int));
        *num = i;

        pthread_create(&thread, NULL, (void*)&runMe, num);
        threads[i] = thread;
        nums[i] = num;
    }

    for (int i=0; i<=(n-1); i++) {
        int* temp;
        pthread_join(threads[i], (void**)&temp);
        sumExitCodes += *temp;
        free(temp);
        free(nums[i]);
    }
    return sumExitCodes;
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
