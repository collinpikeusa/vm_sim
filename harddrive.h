//
// Created by Collin Pike on 12/8/2018.
//

#ifndef PROJECT_6_HARDDRIVE_H
#define PROJECT_6_HARDDRIVE_H
#include <stdio.h>
#include <stdlib.h>
#define DEBUG

/* There is no byte data type in C */
typedef unsigned char byte;

unsigned char * read_backing_store(int pageNumber);

#endif //PROJECT_6_HARDDRIVE_H
