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


/*default page fault handler that assumes there are more frames than pages
* This assumption means we don't need disk and can make page N map to frame N
*/
void page_fault_handler( struct page_table *pt, int page )
{
	page_table_set_entry(pt,page,page,PROT_READ|PROT_WRITE);
	page_table_print(pt);

	printf("page fault on page #%d\n",page);
//	exit(1);
}

/*random page fault handler
* 1) chooses a free frame
* 2) adjusts page table to map page to free frame, with read permissions
* 3) loads page from disk into free frame
* Downside: Prone to throwing out a page that's being used
*/
void page_fault_handler_random(struct page_table *pt, int page){
	
	printf("Faulted page: %i\n", page);

	srand(time(NULL));
	if(!ft){
		ft = malloc(sizeof(struct frame_table));
		ft->frames = malloc(sizeof(int) * page_table_get_nframes(pt));
	}
	// Make default values for frame and bits to fill in from the page table.
	int frame;
	int bits;
	int new_frame;
	int new_bits;

	// TODO: do we need this?
	page_table_get_entry(pt, page, &new_frame,&new_bits);

	int nframes = page_table_get_nframes(pt);
	int nPages = page_table_get_npages(pt);

	char *physmem = page_table_get_physmem(pt);


	// Find if there is an empty frame
	int empty_frame = 0;
	for (int i = 0; i < nframes; i++) {
		if(ft->frames[i]==0){
			printf("(page fault handler) frame: %i\n", i);
			// printf("frame bits: %i", ft->frames[i]);
			page_table_set_entry(pt,page,i,PROT_READ|PROT_WRITE);
			disk_read(disk, page, &physmem[i * PAGE_SIZE]);

			ft->frames[i] = PROT_READ|PROT_WRITE; // TODO: when do we set write permissions?
			empty_frame = 1;
			break;
		}
	}

	 // TODO: revisit get_entry
	if (!empty_frame) {
		// If there are no empty frames, pick a random frame to replace
		int to_replace = lrand48()%nPages;
		page_table_get_entry(pt, to_replace,&frame,&bits);
		disk_write(disk, to_replace, &physmem[frame * PAGE_SIZE]);
		disk_read(disk, page, &physmem[new_frame * PAGE_SIZE]);
		page_table_set_entry(pt, page, frame, PROT_READ);
		page_table_set_entry(pt, to_replace, new_frame, 0);
		printf("random #: %d\n",to_replace);
	}
	

	page_table_print(pt);

	// If there are empty frames, fill an empty frame with the new page
	// Mark the frame as used

	// (save what you are replacing to disk if it has been changed, then remove it)
	// and put that page in it

	// Update page table

	// TODO: why exit? when/do we use it?
	// exit(1);



}

/*
TODO: 
1) finish rand (random replacement)
2) implement fifo (first-in-first-out)
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
	const char *program = argv[4];

	disk = disk_open("myvirtualdisk",npages);
	if(!disk) {
		fprintf(stderr,"couldn't create virtual disk: %s\n",strerror(errno));
		return 1;
	}


	struct page_table *pt = page_table_create( npages, nframes, page_fault_handler_random);
	if(!pt) {
		fprintf(stderr,"couldn't create page table: %s\n",strerror(errno));
		return 1;
	}

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
	return 0;
}
