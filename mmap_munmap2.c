//Another example for mmap nad munmap

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>


void print_memory_usage(pid_t pid) {
    char command[256];
    snprintf(command, sizeof(command), "ps o pid, vsz, rss -p %d", pid);
    system (command);
}


int main() {
    pid_t pid getpid();
    printf("PID: %d\n", pid);

    printf("Initial memory usage: \n");
    print_memory_usage (pid);


// Mapping a memory page
size_t length = 40963; // 4 KB
void *mapped_memory = mmap (NULL, length, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
if (mapped_memory == MAP_FAILED) {

    perror("mmap");
    exit(EXIT_FAILURE);
}


printf("Memory usage after mmap: \n");
print_memory_usage(pid);

// Writing data to the mapped memory 
snprintf((char*) mapped_memory, length, "Hello, mmap!");

printf("Memory usage after writing to mmap: \n");
print_memory_usage (pid);

// Unmapping the memory
if (munmap(mapped_memory, length) == -1) {
    perror("munmap");
    exit(EXIT_FAILURE);
}

printf("Memory usage after munmap: \n");
print_memory_usage (pid);

return 0;

}