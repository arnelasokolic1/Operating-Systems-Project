#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N 3  // Maximum number of requests allowed in the system

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int current_requests = 0;

void thread_exitFailure() {
    printf("Thread %ld exiting due to overload.\n", pthread_self());
    pthread_exit(NULL);
}

void receiveService() {
    printf("Thread %ld receiving service.\n", pthread_self());
    sleep(2);  // Simulate service time
}

void thread_exitSuccess() {
    printf("Thread %ld successfully finished.\n", pthread_self());
    pthread_exit(NULL);
}

void* request_thread(void* arg) {
    pthread_mutex_lock(&mutex);

    if (current_requests >= N) {
        pthread_mutex_unlock(&mutex);
        thread_exitFailure();
    }

    current_requests++;
    printf("Thread %ld added to the system. Current requests: %d\n", pthread_self(), current_requests);

    while (current_requests > 1) {
        pthread_cond_wait(&cond, &mutex);
    }

    pthread_mutex_unlock(&mutex);

    receiveService();

    pthread_mutex_lock(&mutex);
    current_requests--;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);

    thread_exitSuccess();
}

int main() {
    pthread_t threads[10];  // Array to hold thread IDs
    for (int i = 0; i < 10; i++) {
        pthread_create(&threads[i], NULL, request_thread, NULL);
        sleep(1);  // Simulate staggered arrival of requests
    }

    for (int i = 0; i < 10; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}

