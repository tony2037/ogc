#ifndef GC_H
#define GC_H

#include <stddef.h>

void gc_init(void *ptr, size_t limit);
void *gc_alloc(size_t size);
void gc_free(void *ptr);
void gc_run();
void gc_destroy(void);

void gc_dump_internals(void);

void lock(void);
void unlock(void);

void set_multithreading(bool);
void set_multi_stack_start(size_t, void *);

#endif
