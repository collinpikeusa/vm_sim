/*
 * Project 5: backingstore_reader.c
 *
 * This program demonstrates how to read and print the bytes in the backing store.
 *
 * by Xiao Qin.
 */
#include <stdio.h>
#include <stdlib.h>
#include "system.h"
#include "types.h"
#include "physicalmemory.h"
#include "page_table.h"
#include "tlb.h"
#define DEBUG

/* There is no byte data type in C */

char physical_address_choice;
char algorithm_choice;

void welcome_message(void);
void output_address_value_list(const char *output_file_name, address_value_list_t addr_value_list);
void update_address_value_list(logic_address_t l_addr, physical_address_t p_addr, value_t value, address_value_list_t *addr_value_list);
int get_page_num(int l_addr, int *p_num) {
    *p_num = (l_addr>> OFFSET_BITS);
    return 0;
}

int get_offset(int l_addr, int *off) {
    *off = l_addr & PAGE_OFFSET_MASK;
    return 0;
}
uint_t tlb_hits = 0;
uint_t page_faults = 0;
int count;
address_value_list_t address_value_list;

int main ( int argc, char *argv[] ) {

    /* three counters initialized to be 0*/
    uint_t lookups = 0;

    int x;
    FILE *file;
    int i;
    int seek_position;
    fpos_t pos;
    int num_bytes_read;
    byte_t one_byte;


    /* argc should be 2 for correct execution */
    if (argc != 2) {
        /* We print argv[0] assuming it is the program name */
        printf( "usage: %s, <input logic address file>\n", argv[0]);
        return 0;
    }

    welcome_message();

    /* file = fopen(backingstore, "r" );*/
    file = fopen(argv[1], "r" );

    /* fopen returns 0, the NULL pointer, on failure */
    if ( file == 0 ) {
        printf( "Could not open file: %s.\n", argv[1]);
    }
    else {
        /* SEEK_SET: reference position is the beginning of file */
        fseek(file, seek_position, SEEK_SET);
        fgetpos(file, &pos);
        init_tlb();
        /* Read and print data from backingstore */
        while (fgets(addressReadBuffer, 10, file) != NULL) {
            int page_number;
            int offset_number;
            int virtual_addr = atoi(addressReadBuffer); // converting from ascii to int
            int value;
            // 32-bit masking function to extract page number
            get_page_num(virtual_addr, &page_number);
            get_offset(virtual_addr, &offset_number);

            // 32-bit masking function to extract page offset
            int frameNumber;
            int physicalAddress;
            bool isPageFault = TRUE;
            bool isTLBhit = FALSE;
            search_TLB(page_number, &frameNumber, &isTLBhit);
            if(!isTLBhit) {
                search_page_table(page_number, &frameNumber, &isPageFault);
                if (isPageFault) {
                    load_physical_memory(page_number, &frameNumber);
                    update_page_table(page_number, frameNumber);
                    if(algorithm_choice == 2)
                        TLB_replacement_LRU((page_t) page_number, (frame_t) frameNumber);
                    else
                        TLB_replacement_FIFO((page_t) page_number, (frame_t) frameNumber);
                    page_faults++;
                }
                else{
                    if(algorithm_choice == 2)
                        TLB_replacement_LRU((page_t) page_number, (frame_t) frameNumber);
                    else
                        TLB_replacement_FIFO((page_t) page_number, (frame_t) frameNumber);
                }
            }
            else
                tlb_hits++;
            create_physical_address(frameNumber, offset_number, &physicalAddress);
            count++;
            read_physical_memory(frameNumber, offset_number, &value);
            if(physical_address_choice == 'y') {
                printf("Virtual address: %d; Physical address: %d; Value: %d\n", virtual_addr, physicalAddress, value);
            }
            update_address_value_list((logic_address_t) virtual_addr, (physical_address_t) physicalAddress,
                                      (value_t) value, &address_value_list);
        }
        printf("*********************************************************************\n");
        printf("Page fault rate: %.02f%%\n", (double)page_faults/(double)count*100);
        printf("TLB hit rate: %.02f%%\n", (double)tlb_hits/(double)count*100);
        fclose( file );
    }
    output_address_value_list("vm_sim_output.txt", address_value_list);
}

void welcome_message(void) {
    printf("Welcome to Collin Pike's VM Simulator\n");
    printf("Number of logical pages: %d\n", NUM_PAGES);
    printf("Page size: %d bytes\n", PAGE_SIZE);
    printf("Page table size: %d\n", NUM_PAGES);
    printf("TLB size: %d\n", TLB_SIZE);
    printf("Number of physical frames: %d\n", NUM_FRAMES);
    printf("Physical memory size: %d bytes\n", PAGE_SIZE*NUM_FRAMES);
    do {
        printf("\nDisplay All Physical Addresses? [y/n]: ");
        scanf("\n%c", &physical_address_choice);
    } while (physical_address_choice != 'n' && physical_address_choice != 'y');

    do {
        printf("Choose TLB Replacement Strategy [1: FIFO, 2: LRU]: ");
        scanf("\n%c", &algorithm_choice);
    } while (algorithm_choice != '1' && algorithm_choice != '2');
}
void output_address_value_list(const char *output_file_name, address_value_list_t addr_value_list) {
    FILE *output = fopen(output_file_name, "w");
    u_int_t length = addr_value_list.next_ptr;
    int i;
    for(i = 0; i < length; i++) {
        logic_address_t virtual_address = addr_value_list.logic_addresses[i];
        physical_address_t physical_address = addr_value_list.physical_addresses[i];
        value_t value = addr_value_list.values[i];
        fprintf(output, "Virtual address: %d; Physical address: %d; Value: %d\n",virtual_address, physical_address, value);
    }
    fprintf(output, "*********************************************************************\n");
    fprintf(output, "Page fault rate: %.02f%%\n", (double)page_faults/(double)count*100);
    fprintf(output, "TLB hit rate: %.02f%%\n", (double)tlb_hits/(double)count*100);
    fclose(output);
}

void update_address_value_list(logic_address_t l_addr, physical_address_t p_addr, value_t value, address_value_list_t *addr_value_list) {
    u_int_t index = addr_value_list->next_ptr;
    if(index < NUM_PAGES) {
        addr_value_list->physical_addresses[index] = p_addr;
        addr_value_list->logic_addresses[index] = l_addr;
        addr_value_list->values[index] = value;
        addr_value_list->next_ptr++;
    }
}


