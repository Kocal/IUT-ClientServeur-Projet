#include <stdexcept>
#include <cstdio>
#include "grid.h"

Grid::Grid() {
    this->size = 5;
}

Grid::Grid(int size): size(size) {}

void Grid::initPlateau() {
    int i, j;
    
    if(this->size < 0) {
        throw std::logic_error("La taille du plateau est inférieure à 0");
        return;
    }
    
    for(i = 0; i < this->size; i++) {
        for(j = 0; j < this->size; j++) {
            this->plateau[i][j] = ' ';
        }
    }
}

void Grid::printPlateau(void) {
    int y, x;

    if(this->size < 0) {
        throw std::logic_error("La taille du plateau est inférieure à 0");
        return;
    }

    for(y = 0; y < this->size; y++) {
        for(x = 0; x < this->size; x++) {
            wprintf(L"|%lc|", this->plateau[x][y]);
        }

        printf("|\n");

        for(x = 0; x < this->size; x++) {
            printf("|---");
        }

        printf("|\n");
    }
}
