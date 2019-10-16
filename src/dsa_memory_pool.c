#include "dsa_memory_pool.h"

enum {
    __ALIGN = 8,
    __MAX_BYTES = 128,
    __NFREELISTS = __MAX_BYTES / __ALIGN
};

typedef union obj {
    union obj *free_list_link;
    char client_data[1];
} obj;

static char *start_free = NULL;
static char *end_free = NULL;
static size_t heap_size = 0;
static obj * volatile free_list[__NFREELISTS] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};

inline static size_t ROUND_UP(size_t bytes) {
    return (bytes + __ALIGN - 1) & ~(__ALIGN - 1);
}

inline static size_t FREELIST_INDEX(size_t bytes) {
    return (bytes + __ALIGN - 1) / __ALIGN - 1;
}

static char* chunk_alloc(size_t size, int *nobjs) {
    char *result;
    size_t total_bytes = size * (*nobjs);
    size_t bytes_left = end_free - start_free;
    
    if(bytes_left >= total_bytes) {
        result = start_free;
        start_free += total_bytes;
        return result;
    } else if(bytes_left >= size) {
        *nobjs = (int)(bytes_left / size);
        total_bytes = size * (*nobjs);
        result = start_free;
        start_free += total_bytes;
        return result;
    } else {
        size_t bytes_to_get = 2 * total_bytes + ROUND_UP(heap_size >> 4);
        
        if(bytes_left > 0) {
            obj * volatile *my_free_list = free_list + FREELIST_INDEX(bytes_left);
            ((obj*)start_free)->free_list_link = *my_free_list;
            *my_free_list = (obj*)start_free;
        }
        
        start_free = (char*)malloc(bytes_to_get);
        if(NULL == start_free) {
            obj * volatile *my_free_list, *p;
            for(int i = (int)size; i <= __MAX_BYTES; i += __ALIGN) {
                my_free_list = free_list + FREELIST_INDEX(i);
                p = *my_free_list;
                if(NULL != p) {
                    *my_free_list = p->free_list_link;
                    start_free = (char*)p;
                    end_free = start_free + i;
                    return chunk_alloc(size, nobjs);
                }
            }
            end_free = NULL;
            return NULL;
        }
        
        heap_size += bytes_to_get;
        end_free = start_free + bytes_to_get;
        return chunk_alloc(size, nobjs);
    }
}

static void* refill(size_t n) {
    int nobjs = 20;
    obj *result;
    obj * volatile *my_free_list;
    obj *current_obj, *next_obj;
    char *chunk = chunk_alloc(n, &nobjs);
    
    if(1 == nobjs) {
        return chunk;
    }
    
    result = (obj*)chunk;
    my_free_list = free_list + FREELIST_INDEX(n);
    *my_free_list = next_obj = (obj*)(chunk + n);
    
    for(int i = 1; ; ++i) {
        current_obj = next_obj;
        next_obj = (obj*)((char*)next_obj + n);
        if(nobjs - 1 == i) {
            current_obj->free_list_link = NULL;
            break;
        } else {
            current_obj->free_list_link = next_obj;
        }
    }
    
    return result;
}

void* allocate(size_t n) {
    obj *result;
    obj * volatile *my_free_list;
    
    if(n > (size_t)__MAX_BYTES) {
        return malloc(n);
    }
    
    my_free_list = free_list + FREELIST_INDEX(n);
    result = *my_free_list;
    
    if(result == NULL) {
        return refill(ROUND_UP(n));
    }
    
    *my_free_list = result->free_list_link;
    return result;
}

void deallocate(void *p, size_t n) {
    obj *q = (obj*)p;
    obj * volatile *my_free_list;
    
    if(n > (size_t)__MAX_BYTES) {
        free(p);
        return;
    }
    
    my_free_list = free_list + FREELIST_INDEX(n);
    q->free_list_link = *my_free_list;
    *my_free_list = q;
}

void* reallocate(void *p, size_t old_size, size_t new_size) {
    if(old_size > __MAX_BYTES && new_size > __MAX_BYTES) {
        return realloc(p, new_size);
    } else if(ROUND_UP(old_size) == ROUND_UP(new_size)) {
        return p;
    } else {
        void *result = allocate(new_size);
        size_t copy_size = (new_size > old_size? old_size: new_size);
        memcpy(result, p, copy_size);
        deallocate(p, old_size);
        return result;
    }
}
