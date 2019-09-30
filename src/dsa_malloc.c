#include "dsa_malloc.h"

enum {
    ALIGN = 8,
    MAX_BYTES = 128,
    NFREELISTS = MAX_BYTES / ALIGN
};

typedef union obj {
    union obj *free_list_link;
    char client_data[1];
} obj;

static char *start_free = NULL;
static char *end_free = NULL;
static size_t heap_size = 0;
static obj * volatile free_list[NFREELISTS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

inline static size_t round_up(size_t bytes) {
    return (bytes + ALIGN - 1) & ~(ALIGN - 1);
}

inline static size_t free_list_index(size_t bytes) {
    return (bytes + ALIGN - 1) / ALIGN - 1;
}

static char* chunk_alloc(size_t size, int *nobjs) {
    char *result;
    size_t total_bytes = size * (*nobjs);
    size_t bytes_left = end_free - start_free;
    
    if(bytes_left >= total_bytes) {
        result = start_free;
        start_free += total_bytes;
        return result;
    }
    
    if(bytes_left >= size) {
        *nobjs = (int)(bytes_left / size);
        total_bytes = size * (*nobjs);
        result = start_free;
        start_free += total_bytes;
        return result;
    }
    
    size_t bytes_to_get = 2 * total_bytes + round_up(heap_size >> 4);
    
    if(bytes_left > 0) {
        obj * volatile *my_free_list = free_list + free_list_index(bytes_left);
        ((obj*)start_free)->free_list_link = *my_free_list;
        *my_free_list = (obj*)start_free;
    }
    
    start_free = (char*)malloc(bytes_to_get);
    if(NULL == start_free) {
        obj * volatile *my_free_list, *p;
        for(size_t i = size; i <= MAX_BYTES; i += ALIGN) {
            my_free_list = free_list + free_list_index(i);
            p = *my_free_list;
            if(NULL != p) {
                *my_free_list = p->free_list_link;
                start_free = (char*)p;
                end_free = start_free + i;
                return chunk_alloc(size, nobjs);
            }
        }
        end_free = NULL;
    }
    
    heap_size += bytes_to_get;
    end_free = start_free + bytes_to_get;
    return chunk_alloc(size, nobjs);
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
    my_free_list = free_list + free_list_index(n);
    *my_free_list = next_obj = (obj*)(chunk + n);
    
    // TODO: 可以调整为：for(int i = 2; i < n; ++i)
    // TODO: current_obj->free_list_link = NULL;
    for(int i = 2; ; ++i) {
        current_obj = next_obj;
        next_obj = (obj*)((char*)next_obj + n);
        if(nobjs == i) {
            current_obj->free_list_link = NULL;
            break;
        }
        current_obj->free_list_link = next_obj;
    }
    
    return result;
}

void* _allocate(size_t n) {
    obj *result;
    obj * volatile *my_free_list;
    
    if(n > (size_t)MAX_BYTES) {
        return malloc(n);
    }
    
    my_free_list = free_list + free_list_index(n);
    result = *my_free_list;
    
    if(result == 0) {
        return refill(round_up(n));
    }
    
    *my_free_list = result->free_list_link;
    return result;
}

void _deallocate(void *p, size_t n) {
    obj *q = (obj*)p;
    obj * volatile *my_free_list;
    
    if(n > (size_t)MAX_BYTES) {
        free(p);
        return;
    }
    
    my_free_list = free_list + free_list_index(n);
    q->free_list_link = *my_free_list;
    *my_free_list = q;
}

void* _reallocate(void *p, size_t old_size, size_t new_size) {
    if(old_size > MAX_BYTES && new_size > MAX_BYTES) {
        return realloc(p, new_size);
    }
    
    if(round_up(old_size) == round_up(new_size)) {
        return p;
    }
    
    void *result = _allocate(new_size);
    size_t copy_sz = (new_size > old_size? old_size: new_size);
    memcpy(result, p, copy_sz);
    _deallocate(p, old_size);
    return result;
}
