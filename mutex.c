///
// mutex.c - sum a vector of values using multi-threading and a mutex
// compile with: gcc mutex.c -o mutex --std=c99 -lpthread
//
//gcc -std=c99 -Werror -Wall -g -o "%e" "%f"


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


#define NUM_THREADS 16
#define N 10000


typedef struct {
    float *total;
    int n;

    pthread_mutex_t *lock;
    pthread_t thread;

} Worker;


void *run_summation(void *ptr)
{
    Worker *worker = (Worker*)ptr;

    for (int i = 0; i < worker->n; ++i) {
        //TODO: make this thread safe!!

        pthread_mutex_lock(worker->lock);
        (*worker->total)++;
        pthread_mutex_unlock(worker->lock);
    }

    return NULL;
}



int main()
{

    // Global variable for total summation so far
    float total = 0;

    pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
    Worker workers[NUM_THREADS];


    for (int i = 0; i < NUM_THREADS; ++i) {
        // What would be the problem declaring Worker w here?

        Worker *worker = &workers[i];
        worker->total = &total; // Pass the global total into each thread

        worker->lock = &lock;
        worker->n = N;

        pthread_t thread;
        worker->thread = thread;

        pthread_create(&worker->thread, NULL, run_summation, (void*)worker);

        //TODO: Make this run in a thread!
        //run_summation((void*)worker);

    }


    ////////////////////////////////
    // Wait for all the threads we created
    // for(i = ...)
      ////////////////////////////////

    for (i=0; i<NUM_THREADS; i++) {
        pthread_join(workers[i].thread, NULL);
    }

    printf("Final total: %f \n", total);

    return 0;
}

