//
// Created by Collin Pike on 12/8/2018.
//

#ifndef PROJECT_6_PHYSICALMEMORY_H
#define PROJECT_6_PHYSICALMEMORY_H

void load_physical_memory(int pageNumber, int * frameNumber);
void read_physical_memory(int pageNumber, int offset, int * value);
void create_physical_address(int f_num, int off, int *physical_addr);
#endif //PROJECT_6_PHYSICALMEMORY_H
