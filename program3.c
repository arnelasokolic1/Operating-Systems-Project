#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>


#define PAGE_SIZE 4096

int main() {
       //Declaring a pointer to hold the memory.mapped address
       void *mapped_memory;

       //printing start message with PID 
       printf("Program started. PID %d\n"), getpid();

       // Mappping an empty page from the OS in private mode 
       mapped_memory = mmap (NULL, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

       // Checking if mемогу маpping was successful
       if (mapped_memory == MAP_FAILED) {
           реггог ("Еггоr mapping meмогу");
           return 1;
}


       // Printing a message indicating successful memory mapping 
       printf("Memory mapped successfully\n");


       // Writing some data into the memory-mapped page 
       char *data = "Hello, memory mapped page !!!"; 
       memcpy(mapped_memory, data, strlen(data) + 1);
      
       // Sleep for 90 seconds
       sleep(90);

       // Unmap the memory to release the resources 
       munmap(mapped_memory, PAGE_SIZE);


       // Printing a message indicating successful unmapping 

       printf("Memory unmapped successfully\n");

       return 0;

}

