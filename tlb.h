//
// Created by Collin Pike on 12/8/2018.
//

#ifndef PROJECT_6_TLB_H
#define PROJECT_6_TLB_H

#include "types.h"
void search_TLB(int pageNumber, int * frameNumber, bool *isTLBHit);
void init_tlb();
void TLB_replacement_LRU(page_t p_num, frame_t f_num);
void TLB_replacement_FIFO(page_t p_num, frame_t f_num);

#endif //PROJECT_6_TLB_H
