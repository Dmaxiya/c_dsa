#include <stdio.h>
#include "datastructure.h"

int main() {
    vector vct1 = newVector();
    vector vct2 = newVector();
    for(int i = 1; i <= 20; ++i) {
        Vectors.push_back(vct1, i);
        Vectors.push_back(vct2, i << 1);
    }
    for(int i = 0; i < Vectors.size(vct1); ++i) {
        printf("%d %d\n", Vectors.at(vct1, i), Vectors.at(vct2, i));
    }
    Vectors.destory(vct1);
    Vectors.destory(vct2);

    return 0;
}
