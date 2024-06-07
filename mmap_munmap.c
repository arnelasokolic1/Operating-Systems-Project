#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>


int main() {
   // Opening the file
   int fd = open("example.txt", O_RDONLY);
     if (fd == -1) {
        perror("open");
        return 1;
}
// Getting the size of the file
struct stat sb;
    if (fstat(fd, &sb) == -1) {
        perror("fstat");
        close(fd);
    return 1;
}
// Mapping the file into memory
void *addr = mmap (NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (addr == MAP_FAILED) {
    perror("mmap");
    close(fd);
return 1;
}


// Accessing the mapped memory
printf("File contents: \n%.*s\n", (int)sb.st_size, (char *)addr);

// Unmapping the memory
if (munmap(addr, sb.st_size) == -1) {
}
    perror("munmap");

// Closing the file
close(fd);

return 0;
}