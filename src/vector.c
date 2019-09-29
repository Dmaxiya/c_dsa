#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "vector.h"

// 临时使用的 swap 函数，不具有可拓展性
static void swap(void *a, void *b, int size) {
    void *c = malloc(size);
    memcpy(c, a, size);
    memcpy(a, b, size);
    memcpy(b, c, size);
    free(c);
}

// 判断是否需要开辟新空间，在添加新元素之前判断
static bool needIncrease(vector vct) {
    return vct->length >= vct->totalSize;
}

// 重新开辟 listsize * 2 个空间，复制原数据
static void increase(vector vct) {
    vct->totalSize <<= 1;
    if(vct->totalSize == 0) {
        vct->totalSize = 1;
    }
    assert(vct->elem = realloc(vct->elem, vct->totalSize * sizeof(vectorElemType)));
}

static void vectorAssign(vector vct, int n, vectorElemType e) {
    if(vct->totalSize < n) {

    }
}

static vectorElemType vectorAt(vector vct, int index) {
    assert(index >= 0);
    assert(index < vct->length);

    return vct->elem[index];
}

static vectorElemType vectorBack(vector vct) {
    assert(vct->length > 0);

    return vct->elem[vct->length - 1];
}

static int vectorCapacity(vector vct) {
    return vct->totalSize;
}

static void vectorClear(vector vct) {
    vct->length = 0;
}

static vector vectorCopy(vector vct) {
    vector ret = malloc(sizeof(struct vector));
    ret->length = vct->length;
    ret->totalSize = vct->totalSize;
    ret->elem = malloc(sizeof(vectorElemType) * vct->totalSize);
    memcpy(ret->elem, vct->elem, sizeof(vectorElemType) * vct->length);
    return ret;
}

static vectorElemType* vectorData(vector vct) {
    return vct->elem;
}

static void vectorDestory(vector vct) {
    free(vct->elem);
    free(vct);
}

static bool vectorEmpty(vector vct) {
    return vct->length == 0;
}

static void vectorErase(vector vct, int index) {
    assert(index >= 0);
    assert(index < vct->length);

    for(int i = index + 1; i < vct->length; ++i) {
        vct->elem[i - 1] = vct->elem[i];
    }
    --vct->length;
}

static vectorElemType vectorFront(vector vct) {
    assert(vct->length > 0);

    return vct->elem[0];
}

static void vectorInsert(vector vct, int index, vectorElemType e) {
    assert(index >= 0);
    assert(index <= vct->length);

    if(needIncrease(vct)) {
        increase(vct);
    }
    for(int i = vct->length; i > index; --i) {
        vct->elem[i] = vct->elem[i - 1];
    }
    vct->elem[index] = e;
    ++vct->length;
}

static void vectorPopBack(vector vct) {
    if(vct->length == 0) {
        return ;
    }
    --vct->length;
}

static void vectorPushBack(vector vct, vectorElemType e) {
    vectorInsert(vct, vct->length, e);
}

static void vectorReserve(vector vct, int n) {
    if(n <= vct->totalSize) {
        return;
    }

    vct->totalSize = n;
    assert(vct->elem = realloc(vct->elem, vct->totalSize * sizeof(vectorElemType)));
}

static void vectorResize(vector vct, int n, vectorElemType e) {
    if(n <= vct->length) {
        vct->length = n;
    }
    if(n > vct->totalSize) {
        vct->totalSize = n;
        assert(vct->elem = realloc(vct->elem, vct->totalSize * sizeof(vectorElemType)));
    }

    for(int i = vct->length; i < n; ++i) {
        vct->elem[i] = e;
    }
}

static void vectorSet(vector vct, int index, vectorElemType e) {
    assert(index >= 0);
    assert(index < vct->length);

    vct->elem[index] = e;
}

static void vectorShrinkToFit(vector vct) {
    vct->totalSize = vct->length;
    assert(vct->elem = realloc(vct->elem, vct->totalSize * sizeof(vectorElemType)));
}

static int vectorSize(vector vct) {
    return vct->length;
}

static void vectorSwap(vector vct1, vector vct2) {
    swap(&(vct1->length), &(vct2->length), sizeof(int));
    swap(&(vct1->totalSize), &(vct2->totalSize), sizeof(int));
    swap(&(vct1->elem), &(vct2->elem), sizeof(vectorElemType*));
}

static void init() {
    static bool inited = false;
    if(!inited) {
        inited = true;
        Vectors.assign = vectorAssign;
        Vectors.at = vectorAt;
        Vectors.back = vectorBack;
        Vectors.capacity = vectorCapacity;
        Vectors.clear = vectorClear;
        Vectors.data = vectorData;
        Vectors.destory = vectorDestory;
        Vectors.empty = vectorEmpty;
        Vectors.erase = vectorErase;
        Vectors.front = vectorFront;
        Vectors.insert = vectorInsert;
        Vectors.copy = vectorCopy;
        Vectors.pop_back = vectorPopBack;
        Vectors.push_back = vectorPushBack;
        Vectors.reserve = vectorReserve;
        Vectors.resize = vectorResize;
        Vectors.set = vectorSet;
        Vectors.shrink_to_fit = vectorShrinkToFit;
        Vectors.size = vectorSize;
        Vectors.swap = vectorSwap;
    }
}

vector newVector() {
    init();
    vector vct = malloc(sizeof(struct vector));
    memset(vct, 0, sizeof(struct vector));
    return vct;
}
