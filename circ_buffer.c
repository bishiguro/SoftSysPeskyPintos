// Circular buffer and associated methods
// Following tutorial from http://embedjournal.com/implementing-circular-buffer-embedded-c/

#include <stdio.h>
#include <stdlib.h>

typedef struct circBuf_t{
	int *buffer;	// Ideally this should be a const but assigning values to a const in c at run-time is messy
	int head;
	int tail;
	int table_size;	// Ideally this should be a const but assigning values to a const in c at run-time is messy
} circBuf_t;

circBuf_t *make_cb(int size){
	circBuf_t *cb = malloc(sizeof(struct circBuf_t)*100);
	cb->table_size = size;
	cb->head = 0;
	cb->tail = 0;
	cb->buffer = malloc(sizeof(int) * size);
	return cb;
}

int is_buffer_empty(circBuf_t *cb){
	return (cb->head == cb->tail);
}

int is_buffer_full(circBuf_t *cb){
	return ((cb->head + 1) == cb->tail);
}

int cb_push(circBuf_t *cb, int data){
	int next = cb->head + 1;
	if(next >= cb->table_size){
		next = 0;
	}

	if(next == cb->tail){	// circular buffer is full
		return -1;
	}

	cb->buffer[cb->head] = data;
	cb->head = next;
	return 0;
}

int cb_pop(circBuf_t *cb, int *data){
	// empty buffer
	if(is_buffer_empty(cb)){
		return -1;
	}

	int next = cb->tail + 1;
	if(next >= cb->table_size){
		next = 0;
	}
	*data = cb->buffer[cb->tail];
	cb->tail = next;
	return 0;
}