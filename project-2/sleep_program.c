#include <stdio.h>
#include <unistd.h>

int main() {

    // Print start message with PID
    printf("Program started. PID: %d\n", getpid());


    // Sleep for 90 seconds
    sleep(90);

    return 0;
}