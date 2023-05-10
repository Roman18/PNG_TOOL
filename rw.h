#ifndef RW_
#define RW_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

 
void read_bytes_(FILE* f, void* buff, size_t size, 
    const char* source_file, const int source_line);
void print_bytes(void* buff, size_t size, const char* fmt);
void reverse_bytes(void* buff, size_t size);

#define read_bytes(file, buff, size) \
     read_bytes_(file, buff, size, __FILE__, __LINE__)


#endif // RW_