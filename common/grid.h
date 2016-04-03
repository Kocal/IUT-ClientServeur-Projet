#ifndef _GRID_H
#define _GRID_H

class Grid {
       
    const static wchar_t SYMBOL_PLAYER_1 = L'○';
    const static wchar_t SYMBOL_PLAYER_2 = L'×';
    const static wchar_t SYMBOL_PLAYER_3 = L'▵';
    const static wchar_t SYMBOL_PLAYER_4 = L'◽';
    
    public:
        Grid(void);
        Grid(int size);
        
        wchar_t** getPlateau() { return plateau; }
        void printPlateau();
        int getSize() { return size; }
        
    private:
        wchar_t** plateau;
        int size;

        void initPlateau();
};

#endif
