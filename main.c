#include "include/sudokuFunction.h"
#define SIZE 9

int main() {
    short **tab, **tab_full;

    tab=malloc(SIZE*sizeof(short *));
    tab_full=malloc(SIZE*sizeof(short *));
    for(short i=0 ; i<SIZE ;i++){
        tab[i]=malloc(SIZE*sizeof(short));
        tab_full[i]=malloc(SIZE*sizeof(short));
    }

    printf("Hello, World!\n");
    create_sudoku(tab,tab_full,SIZE,40);
    read_sudoku(tab_full,SIZE);
    read_sudoku(tab,SIZE);
    return 0;
}
