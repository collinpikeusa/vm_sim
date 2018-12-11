//
// Created by Collin Pike on 12/8/2018.
//

#include "tlb.h"
#include <stdio.h>

static tlb_t tlb;

void init_tlb() {
    for (int i = 0; i < TLB_SIZE; i++)
        tlb.tlb_entry[i].valid = FALSE;
}

void search_TLB(int page_number, int *frameNumber, bool *isTLBHit) {
    for(int i = 0; i < 16; i ++){
        if(tlb.tlb_entry[i].valid) {
            if (page_number == tlb.tlb_entry[i].page_num) {
                *frameNumber = tlb.tlb_entry[i].frame_num;
                *isTLBHit = TRUE;
            }
        }
    }
}

void TLB_replacement_LRU(page_t p_num, frame_t f_num) {
    for(int i = 0; i < tlb.next_page_ptr; i++){
        tlb.tlb_entry[i].age++;
    }
    if(tlb.next_page_ptr >= TLB_SIZE){
        int oldest = 0;
        int oldestAge = 0;
        for(int i = 0; i < TLB_SIZE; i++){
            if(oldestAge < tlb.tlb_entry[i].age){
                oldestAge = tlb.tlb_entry[i].age;
                oldest = i;
            }
        }
        tlb.tlb_entry[oldest].page_num = p_num;
        tlb.tlb_entry[oldest].frame_num = f_num;
        tlb.tlb_entry[oldest].age = 0;
        tlb.tlb_entry[oldest].valid = TRUE;
    }
    else{
        int tlbSpot = tlb.next_page_ptr;
        tlb.tlb_entry[tlbSpot].page_num = p_num;
        tlb.tlb_entry[tlbSpot].frame_num = f_num;
        tlb.tlb_entry[tlbSpot].age = 0;
        tlb.tlb_entry[tlbSpot].valid = TRUE;
        tlb.next_page_ptr++;
    }
}

void TLB_replacement_FIFO(page_t p_num, frame_t f_num){
    for (int i = 0; i < TLB_SIZE; i++) {
        if (tlb.tlb_entry[i].valid == FALSE) {
            tlb.tlb_entry[i].page_num = p_num;
            tlb.tlb_entry[i].frame_num = f_num;
            tlb.tlb_entry[i].valid = TRUE;
        }
    }


    // If the tlb is full
    tlb.tlb_entry[tlb.next_page_ptr].page_num = p_num;
    tlb.tlb_entry[tlb.next_page_ptr].frame_num = f_num;
    tlb.tlb_entry[tlb.next_page_ptr].valid = TRUE;
    if (tlb.next_page_ptr == 15) {
        tlb.next_page_ptr = 0;
    }
    else {
        tlb.next_page_ptr++;
    }
}
