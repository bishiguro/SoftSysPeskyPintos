/*
Authors: Bonnie Ishiguro, Andrew Pan, Apurva Raman, Jiaxuan (Amy) Wu
Main program for the virtual memory project.
Make all of your modifications to this file.
You may add or rearrange any code or data as you need.
The header files page_table.h and disk.h explain
how to use the page table and disk interfaces.
*/

#include "page_table.h"
#include "disk.h"
#include "program.h"
#include "circ_buffer.c"

#include <sys/mman.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct disk *disk;

/*frame table*/
struct frame_table{
	int *frames;
};

struct frame_table *ft;

circBuf_t *cb;

int faultCounter = 0;
int diskReadCounter = 0;
int diskWriteCounter = 0;

/*random page fault handler
* 1) chooses a free frame
* 2) adjusts page table to map page to free frame, with read permissions
* 3) loads page from disk into free frame
* Downside: Prone to throwing out a page that's being used
*/
void page_fault_handler_random(struct page_table *pt, int page){
	printf("Faulted page: %i\n", page);
	faultCounter++;

	// Make default values for frame and bits to fill in from the page table.
	int frame;
	int bits;
	int ref_bits;

	int new_frame;
	int new_bits;
	int new_ref_bits;

	page_table_get_entry(pt, page, &new_frame,&new_bits,&new_ref_bits);

	int nframes = page_table_get_nframes(pt);
	int nPages = page_table_get_npages(pt);

	char *physmem = page_table_get_physmem(pt);


	if(!ft){
		ft = malloc(sizeof(struct frame_table));
		ft->frames = malloc(sizeof(int) * page_table_get_nframes(pt));
	}

	int empty_frame = 0;

	if (new_bits == PROT_READ) {
		page_table_set_entry(pt, page, new_frame, PROT_READ|PROT_WRITE, 0);
		ft->frames[new_frame] = PROT_READ | PROT_WRITE;
	}
	else if (new_bits == (PROT_READ | PROT_WRITE)) {
		printf("Error. RW pages should not fault.\n");
	}
	else {
		// Find if there is an empty frame
		int i;
		for (i = 0; i < nframes; i++) {
			if(ft->frames[i]==0){
				page_table_set_entry(pt,page,i,PROT_READ, 0);
				ft->frames[i] = PROT_READ;
				disk_read(disk, page, &physmem[i * PAGE_SIZE]);
				diskReadCounter++;

				empty_frame = 1;
				break;
			}
		}
		// TODO: create a struct of input arguments to pass around including which fault handler to run
		if(!empty_frame){
			unsigned short seed = clock();
			seed48(&seed);
			int to_replace = lrand48()%nPages;
			page_table_get_entry(pt, to_replace,&frame,&bits,&ref_bits);
			if (ref_bits == PROT_READ|PROT_WRITE) {
				disk_write(disk, to_replace, &physmem[frame * PAGE_SIZE]);
				diskWriteCounter++;
			}
			disk_read(disk, page, &physmem[new_frame * PAGE_SIZE]);
			diskReadCounter++;
			page_table_set_entry(pt, page, frame, PROT_READ, 0);
			page_table_set_entry(pt, to_replace, new_frame, 0, 0);
			printf("random #: %d\n",to_replace);

			ft->frames[frame] = PROT_READ;
			ft->frames[new_frame] = 0;
		}
	}
	// page_table_print(pt);

	// TODO: why exit? when/do we use it?
	// exit(1);
}



void page_fault_handler_fifo(struct page_table *pt, int page){
	printf("Faulted page: %i\n", page);
	faultCounter++;

	// Make default values for frame and bits to fill in from the page table.
	int frame;
	int bits;
	int ref_bits;

	int new_frame;
	int new_bits;
	int new_ref_bits;

	page_table_get_entry(pt, page, &new_frame,&new_bits,&new_ref_bits);

	int nframes = page_table_get_nframes(pt);
	int nPages = page_table_get_npages(pt);

	char *physmem = page_table_get_physmem(pt);

	int empty_frame = 0;

	if(!ft){
		ft = malloc(sizeof(struct frame_table));
		ft->frames = malloc(sizeof(int) * page_table_get_nframes(pt));
	}
	if(!cb){
		cb = make_cb(nPages);
	}

	if (new_bits == PROT_READ) {
		page_table_set_entry(pt, page, new_frame, PROT_READ|PROT_WRITE, 0);
		ft->frames[new_frame] = PROT_READ | PROT_WRITE;
	}
	else if (new_bits == (PROT_READ | PROT_WRITE)) {
		printf("Error. RW pages should not fault.\n");
	}
	else {
		// Find if there is an empty frame
		int i;
		for (i = 0; i < nframes; i++) {
			if(ft->frames[i]==0) {
				page_table_set_entry(pt,page,i,PROT_READ, 0);
				ft->frames[i] = PROT_READ; // what are we doing with this frame?

				disk_read(disk, page, &physmem[i * PAGE_SIZE]);
				diskReadCounter++;

				empty_frame = 1;
				cb_push(cb, page);
				break;
			}

		}
		// TODO: create a struct of input arguments to pass around including which fault handler to run

		if(!empty_frame){
			int *to_replace = malloc(sizeof(*to_replace));
			cb_pop(cb, to_replace);

			page_table_get_entry(pt, *to_replace,&frame,&bits, &ref_bits);
			if (ref_bits == PROT_READ|PROT_WRITE) {
				disk_write(disk, *to_replace, &physmem[frame * PAGE_SIZE]);
				diskWriteCounter++;
			}
			disk_read(disk, page, &physmem[new_frame * PAGE_SIZE]);
			diskReadCounter++;
			page_table_set_entry(pt, page, frame, PROT_READ, 0);
			cb_push(cb, page);
			page_table_set_entry(pt, *to_replace, new_frame, 0, 0);

			ft->frames[frame] = PROT_READ;
			ft->frames[new_frame] = 0;
		}
	}

	// page_table_print(pt);
}

void page_fault_handler_second_chance (struct page_table *pt, int page){
	printf("Faulted page: %i\n", page);
	faultCounter++;

	// Make default values for frame and bits to fill in from the page table.
	int frame;
	int bits;
	int ref_bits;

	int new_frame;
	int new_bits;
	int new_ref_bits;

	page_table_get_entry(pt, page, &new_frame,&new_bits,&new_ref_bits);

	int nframes = page_table_get_nframes(pt);
	int nPages = page_table_get_npages(pt);

	char *physmem = page_table_get_physmem(pt);

	int empty_frame = 0;

	if(!ft){
		ft = malloc(sizeof(struct frame_table));
		ft->frames = malloc(sizeof(int) * page_table_get_nframes(pt));
	}
	if(!cb){
		cb = make_cb(nPages);
	}

	if (new_bits == PROT_READ) {
		page_table_set_entry(pt, page, new_frame, PROT_READ|PROT_WRITE, 1);
		ft->frames[new_frame] = PROT_READ | PROT_WRITE;
	}
	else if (new_bits == (PROT_READ | PROT_WRITE)) {
		printf("Error. RW pages should not fault.\n");
	}
	else {
		// Find if there is an empty frame
		int i;
		for (i = 0; i < nframes; i++) {
			if(ft->frames[i]==0) {
				page_table_set_entry(pt,page,i,PROT_READ, new_ref_bits);
				ft->frames[i] = PROT_READ;
				disk_read(disk, page, &physmem[i * PAGE_SIZE]);
				diskReadCounter++;

				empty_frame = 1;
				cb_push(cb, page);
				break;
			}

		}

		if(!empty_frame){
			int j;
			for (j = 0; j < nPages; j++) {
				int *sc_page = malloc(sizeof(*sc_page));
				cb_pop(cb, sc_page);
				page_table_get_entry(pt, *sc_page, &frame, &bits, &ref_bits);

				if (ref_bits == 1) {
					// set reference bit to 0
					page_table_set_entry(pt, *sc_page, frame, bits, 0);
					cb_push(cb, *sc_page);
				}
				else {
					if (ref_bits == PROT_READ|PROT_WRITE) {
						disk_write(disk, *sc_page, &physmem[frame * PAGE_SIZE]);
						diskWriteCounter++;
					}

					disk_read(disk, page, &physmem[new_frame * PAGE_SIZE]);
					diskReadCounter++;

					page_table_set_entry(pt, page, frame, PROT_READ, 0);
					cb_push(cb, page);
					page_table_set_entry(pt, *sc_page, new_frame, 0, 0);

					ft->frames[frame] = PROT_READ;
					ft->frames[new_frame] = 0;
					break;
				}
			}
		}
	}
	// page_table_print(pt);
}

// TODO: make this a handler that performs operations then passes off to whatever case we're running
void page_fault_handler( struct page_table *pt, int page )
{
	printf("Faulted page: %i\n", page);
	// page_table_print(pt);
}

/*
TODO:
3) implement custom algorithm
TODO:
1) describe custom page replacement algorithm
2) explain why one algorithm works better than another
3) include which command line arguments we ran to reproduce work
*/
int main( int argc, char *argv[] )
{
	if(argc!=5) {
		printf("use: virtmem <npages> <nframes> <rand|fifo|custom> <sort|scan|focus>\n");
		return 1;
	}

	int npages = atoi(argv[1]);
	int nframes = atoi(argv[2]);
	const char *policy = argv[3];
	const char *program = argv[4];

	disk = disk_open("myvirtualdisk",npages);
	if(!disk) {
		fprintf(stderr,"couldn't create virtual disk: %s\n",strerror(errno));
		return 1;
	}

	struct page_table *pt;
	if (!strcmp(policy, "fifo")){
		//printf("FIFO\n");
		pt = page_table_create(npages, nframes, page_fault_handler_fifo);
	}

	else if(!strcmp(policy, "rand")){
		//printf("RAND\n");
		pt = page_table_create(npages, nframes, page_fault_handler_random);
	}

	else if(!strcmp(policy, "second-chance")) {
		pt = page_table_create(npages, nframes, page_fault_handler_second_chance);
	}

	else {
		printf("Invalid replacement policy. Using random replacement as default.\n");
		pt = page_table_create(npages, nframes, page_fault_handler_random);
	}

	if(!pt) {
		fprintf(stderr,"couldn't create page table: %s\n",strerror(errno));
		return 1;
	}


	// struct page_table *pt = page_table_create( npages, nframes, page_fault_handler_fifo);
	// if(!pt) {
	// 	fprintf(stderr,"couldn't create page table: %s\n",strerror(errno));
	// 	return 1;
	// }

	char *virtmem = page_table_get_virtmem(pt);

	char *physmem = page_table_get_physmem(pt);

	if(!strcmp(program,"sort")) {
		sort_program(virtmem,npages*PAGE_SIZE);

	} else if(!strcmp(program,"scan")) {
		scan_program(virtmem,npages*PAGE_SIZE);

	} else if(!strcmp(program,"focus")) {
		focus_program(virtmem,npages*PAGE_SIZE);

	} else {
		fprintf(stderr,"unknown program: %s\n",argv[3]);

	}

	page_table_delete(pt);
	disk_close(disk);

	//TODO: print total number of page faults, disk reads, disk writes
	printf("Page faults: %i\n", faultCounter);
	printf("Disk reads: %i\n", diskReadCounter);
	printf("Disk writes: %i\n", diskWriteCounter);

	return 0;
}
