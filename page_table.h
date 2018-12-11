//
// Created by Collin Pike on 12/8/2018.
//

#ifndef PROJECT_6_PAGE_TABLE_H
#define PROJECT_6_PAGE_TABLE_H

#include "system.h"
void update_page_table(int pageNumber, int frame);
void search_page_table(int pageNumber, int * frameNumber, bool *isPageFault);

#endif //PROJECT_6_PAGE_TABLE_H
