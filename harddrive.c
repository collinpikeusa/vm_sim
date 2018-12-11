//
// Created by Collin Pike on 12/8/2018.
//

#include "harddrive.h"


unsigned char * read_backing_store(int pageNumber) {
    const char backingstore[] = "BACKING_STORE";
    static unsigned char physicialmemory[256];
    FILE *file;
    int i;
    int seek_position;
    fpos_t pos;
    int num_bytes_read;
    byte one_byte;

    /*
     * Convert strings into seek_position and num_bytes_read
     * We assume argv[1] is seek_position and argv[2] is num_bytes_read
     */
    seek_position = pageNumber * 256;
    num_bytes_read = 256;

    file = fopen(backingstore, "r" );

    /* fopen returns 0, the NULL pointer, on failure */
    if ( file == 0 ) {
        printf( "Could not open file: %s.\n", backingstore);
    }
    else {
        /* SEEK_SET: reference position is the beginning of file */
        fseek(file, seek_position, SEEK_SET);
        fgetpos(file, &pos);

        /* Read and print data from backingstore */
        for (i = 0; i < num_bytes_read; i++) {
            fread(&one_byte, 1, 1, file);
            /* printf prints one byte as hex */
            physicialmemory[i] = one_byte;
            /*
             * Note: If one_byte's data type is int,
             * then we have to use a bit mask: one_byte&0xFF
             */
        }
        fclose( file );
    }
    return physicialmemory;
}
