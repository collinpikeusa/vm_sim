//
// Created by Collin Pike on 12/8/2018.
//

#include "physicalmemory.h"
#include "harddrive.h"
#include "types.h"

unsigned char * physicalMemory[256];
int nextFrame = 0;

void load_physical_memory(int pageNumber, int * frameNumber) {
    physicalMemory[nextFrame] = read_backing_store(pageNumber);
    *frameNumber = nextFrame;
    nextFrame++;
}
void read_physical_memory(int frameNumber, int offset, int * value) {
    *value = physicalMemory[frameNumber][offset];
}

void create_physical_address(int f_num, int off, int *physical_addr) {
    *physical_addr = f_num << OFFSET_BITS | off;
}

