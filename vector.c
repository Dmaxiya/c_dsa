#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "vector.h"

// 判断是否需要开辟新空间，在添加新元素之前判断
static bool needIncrease(vector vct) {
    return vct->length >= vct->totalSize;
}

// 重新开辟 listsize * 2 个空间，复制原数据
static void increase(vector vct) {
    vct->totalSize <<= 1;
    assert(vct->elem = realloc(vct->elem, vct->totalSize * sizeof(vectorElemType)));
}

static void vectorAssign(vector vct, int size, vectorElemType e) {

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

static int vectorMaxSize(vector vct) {
    return vct->totalSize;
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

static void vectorReserve(vector vct, int size) {

}

static void vectorResize(vector vct, int size, vectorElemType e) {}

static void vectorSet(vector vct, int index, vectorElemType e) {
    assert(index >= 0);
    assert(index < vct->length);

    vct->elem[index] = e;
}

static void vectorShrinkToFit(vector vct) {}

static int vectorSize(vector vct) {
    return vct->length;
}

static void vectorSwap(vector vct1, vector vct2) {}

const int initSize = 1;

vector newVector() {
    static bool inited = false;
    vector vct = malloc(sizeof(struct vector));
    vct->length = 0;
    vct->totalSize = 1;
    vct->elem = malloc(sizeof(vectorElemType));
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
        Vectors.max_size = vectorMaxSize;
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
    return vct;
}
