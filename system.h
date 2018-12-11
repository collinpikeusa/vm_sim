//
// Created by Collin Pike on 12/2/2018.
//

#ifndef PROJECT_6_SYSTEM_H
#define PROJECT_6_SYSTEM_H

#define NUM_PAGES   256	/* total number of pages in virtual memory space */
#define NUM_FRAMES  256	/* total number of frames in physical memory space */

#define PAGE_SIZE   256	/* number of bytes in a page or frame */
#define TLB_SIZE    16	/* number of entries in the TLB */

#define OFFSET_BITS 8	/* number of bits required to address a byte in a page */

#define PAGE_OFFSET_MASK 0xFF /* mask to extract the offset from a logical address */
char addressReadBuffer[10];

typedef enum{FALSE, TRUE} bool;
typedef unsigned int u_int_t;

#endif //PROJECT_6_SYSTEM_H
