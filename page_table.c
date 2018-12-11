//
// Created by Collin Pike on 12/8/2018.
//

#include "page_table.h"
#include "types.h"
#include <stdio.h>

page_table_t pageTable;

void update_page_table(int pageNumber, int frame){
    pageTable.tlb_entry[pageNumber].page_num = (page_t) pageNumber;
    pageTable.tlb_entry[pageNumber].frame_num = (frame_t) frame;
    pageTable.next_tlb_ptr++;
}

void search_page_table(int pageNumber, int * frameNumber, bool *isPageFault){
    for(int i = 0; i < 256; i ++){
        if(pageNumber == pageTable.tlb_entry[i].page_num){
            *frameNumber = pageTable.tlb_entry[i].frame_num;
            *isPageFault = FALSE;
        }
    }
}