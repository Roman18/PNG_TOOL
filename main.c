#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>

#include <stdbool.h>

#include "./rw.h"

#define PNG_HDR_SIZE 8



void usage(int count, const char* prog_name){
    if(count < 2){
        fprintf(stderr, "Usage: %s <input.png>\n", prog_name);
        exit(EXIT_FAILURE);
    }
}


bool check_png_signature(FILE *f){
    uint8_t buffer[PNG_HDR_SIZE];

    const uint8_t header[] = {137, 80, 78, 71, 13, 10, 26, 10};

    read_bytes(f, buffer, PNG_HDR_SIZE);
    //print_bytes(buffer, PNG_HDR_SIZE, "%u ");

    return memcmp(buffer, header, PNG_HDR_SIZE) == 0;
}

int main(int argc, char const *argv[])
{
    
    usage(argc, argv[0]);
    FILE *f = fopen(argv[1], "rb");

    if(f == NULL){
        fprintf(stderr, "ERROR: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    if(!check_png_signature(f)){
        fprintf(stderr, "Wrong PNG signature\n");
        exit(1);
    }
    uint32_t chunk_len;
    uint8_t chunk_type[4];
   // uint8_t *chunk_data = NULL;
    uint32_t crc;
    int index = 1;
    uint8_t iend_type[] = {73, 69, 78, 68, 32};
    while(1){
        printf("Chunk # %d\n\n", index);
        read_bytes(f, &chunk_len, sizeof(chunk_len));
        reverse_bytes(&chunk_len, sizeof(chunk_len));

        read_bytes(f, &chunk_type, sizeof(chunk_type));

        fseek(f, chunk_len, SEEK_CUR);

        //read_bytes(f, chunk_data, chunk_len);

        read_bytes(f, &crc, sizeof(crc));

        printf("Size of chunk: %d\n", chunk_len);

        printf("Chunk type: ");
        print_bytes(&chunk_type, sizeof(chunk_type), "%c");

        //print_bytes(chunk_data, chunk_len, "%u ");

        printf("CRC: 0x%08X\n", crc);
        ++index;
        printf("\n\n");

        if(memcmp(chunk_type, iend_type, 4) == 0)
        {
            break;
        }

    }


    /*
    read_header(f);

    Chunk *chunk = malloc(sizeof(Chunk));

    read_chunk(f);    
    */

    
    
    fclose(f);
    return EXIT_SUCCESS;
}


typedef struct{
    uint32_t len;
    uint32_t type;
    void *data;
    uint32_t crc;
}Chunk;