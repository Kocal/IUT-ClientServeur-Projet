#include <cstdio>
#include "util.h"

/**
 * Initialise un tableau à deux-dimensions avec une valeur de 0
 */
void init2DimArray(int **array, int key1, int key2) {
    int i, j;
    
    array = new int*[key1];
    
    for(i = 0; i < key1; i++) {
        array[i] = new int[key2];
        
        for(j = 0; j < key2; j++) {
            array[i][j] = 0;
        } 
    }
}