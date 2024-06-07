#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define MAX_REQUESTS 5 // Maximum number of requests that can be handled concurrently



pthread_mutex_t mutex;
pthread_cond_t cond;
sem_t semaphore;
int request_count = 0; // To track the number of active requests


// Function to be called upon successful thread completion
void thread_exitSuccess() {
printf("Thread completed successfully.\n");
pthread_exit(NULL);

}


// Function to be called upon thread failure
void thread_exitFailure() {
printf("Thread failed.\n");
pthread_exit(NULL);

}

// Placeholder function to simulate service reception
void receiveService() {
printf("Service received.\n");
// Simulate service processing time
sleep (2);

}

// Initialize synchronization mechanisms
void initialize() {
pthread_mutex_init(&mutex, NULL);
pthread_cond_init(&cond, NULL); sem_init(&semaphore, 0, MAX_REQUESTS);

}


// Server function to accept and handle client requests
void* server (void* arg) {
     while (1) {
       pthread_mutex_lock(&mutex);


       // If request queue is full, wait for a signal
       while (request_count >= MAX_REQUESTS) {
       pthread_cond_wait(&cond, &mutex);
    }


       // Accept a new request
        request_count++;
        printf("Request received. Active requests: %d\n", request_count);


        // Create a new thread to handle the request
         pthread_t thread;
         pthread_create(&thread, NULL, handle_request, NULL);
         pthread_detach (thread);

     }


         pthread_mutex_unlock(&mutex);
     return NULL;

    }

    // Request handler function (thread) 
    void* handle_request(void* arg) {
    pthread_mutex_lock(&mutex);

       // If too many requests, exit with failure
       if (request_count > MAX_REQUESTS){ 
        pthread_mutex_unlock(&mutex);
        thread_exitFailure(); 
        return NULL;
}

     // Proceed to receive service
      receiveService();


     // Decrease the request count after service
     request_count--;



     // Signal waiting threads that a request has been processed 
     pthread_cond_signal(&cond);


     pthread_mutex_unlock(&mutex);


     // Exit successfully 
     hread_exitSuccess(); 
     return NULL;
}
int main() { 
    initialize();

     // Creating and starting the server thread 
     pthread_t server_thread;
     pthread_create(&server_thread, NULL, server, NULL);
     pthread_join (server_thread, NULL);
return 0;

}