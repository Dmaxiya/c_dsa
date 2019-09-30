#include "dsa_vector.h"

// 临时使用的 swap 函数，不具有可拓展性
static void swap(void *a, void *b, int size) {
    void *c = malloc(size);
    memcpy(c, a, size);
    memcpy(a, b, size);
    memcpy(b, c, size);
    free(c);
}

// 判断是否需要开辟新空间，在添加新元素之前判断
static bool need_increase(vector vct) {
    return vct->length >= vct->total_size;
}

// 重新开辟 listsize * 2 个空间，复制原数据
static void increase(vector vct) {
    vct->total_size <<= 1;
    if(vct->total_size == 0) {
        vct->total_size = 1;
    }
    assert(vct->elem = realloc(vct->elem, vct->total_size * sizeof(vector_elem_type)));
}

static void vector_assign(vector vct, int n, vector_elem_type e) {
    if(vct->total_size < n) {
        vct->total_size = n;
        assert(vct->elem = realloc(vct->elem, vct->total_size * sizeof(vector_elem_type)));
    }
    
    vct->length = n;
    for(int i = 0; i < n; ++i) {
        vct->elem[i] = e;
    }
}

static vector_elem_type vector_at(vector vct, int index) {
    assert(index >= 0);
    assert(index < vct->length);

    return vct->elem[index];
}

static vector_elem_type vector_back(vector vct) {
    assert(vct->length > 0);

    return vct->elem[vct->length - 1];
}

static int vector_capacity(vector vct) {
    return vct->total_size;
}

static void vector_clear(vector vct) {
    vct->length = 0;
}

static vector vector_copy(vector vct) {
    vector ret = malloc(sizeof(struct vector));
    ret->length = vct->length;
    ret->total_size = vct->total_size;
    ret->elem = malloc(sizeof(vector_elem_type) * vct->total_size);
    memcpy(ret->elem, vct->elem, sizeof(vector_elem_type) * vct->length);
    return ret;
}

static vector_elem_type* vector_data(vector vct) {
    return vct->elem;
}

static void vector_destory(vector vct) {
    free(vct->elem);
    free(vct);
}

static bool vector_empty(vector vct) {
    return vct->length == 0;
}

static void vector_erase(vector vct, int index) {
    assert(index >= 0);
    assert(index < vct->length);

    for(int i = index + 1; i < vct->length; ++i) {
        vct->elem[i - 1] = vct->elem[i];
    }
    --vct->length;
}

static vector_elem_type vector_front(vector vct) {
    assert(vct->length > 0);

    return vct->elem[0];
}

static void vector_insert(vector vct, int index, vector_elem_type e) {
    assert(index >= 0);
    assert(index <= vct->length);

    if(need_increase(vct)) {
        increase(vct);
    }
    for(int i = vct->length; i > index; --i) {
        vct->elem[i] = vct->elem[i - 1];
    }
    vct->elem[index] = e;
    ++vct->length;
}

static void vector_pop_back(vector vct) {
    if(vct->length == 0) {
        return ;
    }
    --vct->length;
}

static void vector_push_back(vector vct, vector_elem_type e) {
    vector_insert(vct, vct->length, e);
}

static void vector_reserve(vector vct, int n) {
    if(n <= vct->total_size) {
        return;
    }

    vct->total_size = n;
    assert(vct->elem = realloc(vct->elem, vct->total_size * sizeof(vector_elem_type)));
}

static void vector_resize(vector vct, int n, vector_elem_type e) {
    if(n <= vct->length) {
        vct->length = n;
    }
    if(n > vct->total_size) {
        vct->total_size = n;
        assert(vct->elem = realloc(vct->elem, vct->total_size * sizeof(vector_elem_type)));
    }

    for(int i = vct->length; i < n; ++i) {
        vct->elem[i] = e;
    }
}

static void vector_set(vector vct, int index, vector_elem_type e) {
    assert(index >= 0);
    assert(index < vct->length);

    vct->elem[index] = e;
}

static void vector_shrink_to_fit(vector vct) {
    vct->total_size = vct->length;
    assert(vct->elem = realloc(vct->elem, vct->total_size * sizeof(vector_elem_type)));
}

static int vector_size(vector vct) {
    return vct->length;
}

static void vector_swap(vector vct1, vector vct2) {
    swap(&(vct1->length), &(vct2->length), sizeof(int));
    swap(&(vct1->total_size), &(vct2->total_size), sizeof(int));
    swap(&(vct1->elem), &(vct2->elem), sizeof(vector_elem_type*));
}

static void init() {
    static bool inited = false;
    if(!inited) {
        inited = true;
        Vectors.assign = vector_assign;
        Vectors.at = vector_at;
        Vectors.back = vector_back;
        Vectors.capacity = vector_capacity;
        Vectors.clear = vector_clear;
        Vectors.data = vector_data;
        Vectors.destory = vector_destory;
        Vectors.empty = vector_empty;
        Vectors.erase = vector_erase;
        Vectors.front = vector_front;
        Vectors.insert = vector_insert;
        Vectors.copy = vector_copy;
        Vectors.pop_back = vector_pop_back;
        Vectors.push_back = vector_push_back;
        Vectors.reserve = vector_reserve;
        Vectors.resize = vector_resize;
        Vectors.set = vector_set;
        Vectors.shrink_to_fit = vector_shrink_to_fit;
        Vectors.size = vector_size;
        Vectors.swap = vector_swap;
    }
}

vector newVector() {
    init();
    vector vct = malloc(sizeof(struct vector));
    memset(vct, 0, sizeof(struct vector));
    return vct;
}
