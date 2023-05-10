#include "./rw.h"

void read_bytes_(FILE*f, void*buffer, size_t size,
 const char* source_file, const int source_line)
 
{

    size_t n = fread(buffer, size, 1, f);
    if(n != 1){
        if(ferror(f)){
            fprintf(stderr, "%s:%d ERROR: Could not read the PNG file\n", 
                source_file, source_line);
        }else if(feof(f)){
            fprintf(stderr, "%s:%d ERROR: Reached end of file before finishing\n", 
                source_file, source_line);
        }else{
            fprintf(stderr, "%s:%d Something went wrong during reading the PNG file\n", 
                source_file, source_line);
        }
        exit(EXIT_FAILURE);
    }

}

void print_bytes(void *buff, size_t size, const char* fmt){
    uint8_t *buffer = buff;
    for(size_t i = 0; i < size; i++){

        printf(fmt, buffer[i]);

    }
    printf("\n");
}

void reverse_bytes(void *buff, size_t size){

    uint8_t *buffer = buff;

    for (size_t i = 0; i < size/2; i++)
    {
        uint8_t t = buffer[i];
        buffer[i] = buffer[size - i - 1];
        buffer[size - i - 1] = t;
    }
    
}