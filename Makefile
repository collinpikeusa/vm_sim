CC=gcc
CFLAGS=-I.
DEPS = harddrive.h page_table.h physicalmemory.h system.h types.h tlb.h
OBJ = harddrive.c page_table.c physicalmemory.c vm_sim.c tlb.c

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

vm_sim: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)