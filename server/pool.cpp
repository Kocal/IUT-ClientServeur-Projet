#include "../common/conf.h"
#include "pool.h"

#include <cstdlib>

int* findPool(int **pools, int mode) {
    int *pool = NULL;
    int _pool, _player;

    for(_pool = 0; _pool < MAX_POOLS; _pool++) {

        if(mode == POOL_FIND_MODE::EMPTY) {
            bool isEmpty = true;

            for(_player = 0; _player < MAX_PLAYERS; _player++) {
                if(pools[_pool][_player] != -1) {
                    isEmpty = false;
                }
            }

            if(isEmpty) {
                pool = pools[_pool];
            }

        } else if(mode == POOL_FIND_MODE::WAITING) {
            for(_player = 1; _player < MAX_PLAYERS - 1; _player++) {
                // Si on a un joueur présent, et qu'il y a une place vide avant ou après lui
                if(pools[_pool][_player] != -1 && (pools[_pool][_player - 1] == -1 || pools[_pool][_player + 1] == -1)) {
                    pool = pools[_pool];
                    break;
                }
            }
        }

        if(pool != NULL) {
            break;
        }
    }

    return NULL;
}
