#ifndef DSA_MALLOC_H_
#define DSA_MALLOC_H_

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

void* _allocate(size_t n);
void _deallocate(void *p, size_t n);
void* _reallocate(void *p, size_t old_size, size_t new_size);

#endif // DSA_MALLOC_H_
