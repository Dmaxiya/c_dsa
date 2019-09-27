#include <stdio.h>
#include "datastructure.h"

int main() {
    vector vct1 = newVector();
    vector vct2 = newVector();
    for(int i = 1; i <= 4; ++i) {
        Vectors.push_back(vct1, i);
    }
    for(int i = 0; i < 5; ++i) {
        Vectors.push_back(vct2, i);
    }
    for(int i = 0; i < Vectors.size(vct1); ++i) {
        printf("%d ", Vectors.at(vct1, i));
    }
    printf("\n");
    for(int i = 0; i < Vectors.size(vct2); ++i) {
        printf("%d ", Vectors.at(vct2, i));
    }
    printf("\n");
    printf("\n");
    Vectors.swap(vct1, vct2);
    for(int i = 0; i < Vectors.size(vct1); ++i) {
        printf("%d ", Vectors.at(vct1, i));
    }
    printf("\n");
    for(int i = 0; i < Vectors.size(vct2); ++i) {
        printf("%d ", Vectors.at(vct2, i));
    }
    printf("\n");

    Vectors.destory(vct1);
    Vectors.destory(vct2);

    return 0;
}
