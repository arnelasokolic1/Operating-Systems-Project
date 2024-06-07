#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>


int main() {
printf("Process ID: %d\n", getpid());


// Initial sleep to observe initial memory usage 
sleep (30);

// Map a memory page
void *addr mmap (NULL, 4096, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0); if (addr == MAP_FAILED) {
    perror("mmap");
    exit(EXIT_FAILURE);
}
printf("Memory mapped\n");


// Sleep to observe memory usage after mapping 
sleep (30);

// Write to the mapped memory
strcpy((char *)addr, "Hello, World!");
printf("Written to memory mapped page\n");

// Sleep to observe memory usage after writing 
sleep (30);

// Unmap the memory
if (munmap(addr, 4096)== -1){
    perror("munmap");
    exit(EXIT_FAILURE);
}
printf("Memory unmapped\n");

// Final sleep to observe memory usage after unmapping 
sleep (30);

return 0;

}