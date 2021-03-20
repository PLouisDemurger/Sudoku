#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define SIZE 9

typedef enum{
    TRUE=1,
    FALSE=0
}BOOL;

typedef struct{
    short *val_restante;
    short nb;
}value;

void init_sudoku(short **tab, short size){
    for(short i=0 ; i < size ; i++) {
        for (short j = 0; j < size; j++) {
            tab[i][j] = 0;
        }
    }
}

void read_sudoku(short **tab, short size){
    for(short i=0 ; i < size ; i++){
        if((i)%3==0){
            printf("+++++++++++++++++++++++++++++++++++++\n");
        }
        else
            printf("|-----------|-----------|-----------|\n");
        printf("|");
        for(short j=0 ; j < size ; j++){
            if(tab[i][j]==0)
                printf("   |");
            else
                printf(" %hd |",tab[i][j]);
        }
        printf("\n");
    }
    printf("++++++++++++++++++++++++++++++++++++++\n");
}

value get_value(short **tab, short i, short j, short size){
    short tab_value[size];
    short x1, y1;
    value return_value;
    return_value.val_restante = malloc(sizeof(short)*size);
    for(short z=0; z<size; z++){
        tab_value[z]=0;
        return_value.val_restante[z]=-1;
    }
    for(short z=1; z<=size; z++){
        y1=(short)(i-i%(short)sqrt(size));
        x1=(short)(j-j%(short)sqrt(size));
        // LECTURE CASE
        for(short a=y1  ; a <= i ; a++){
            if(a!=i){
                for(short b=x1 ; b < x1+3 ; b++){
                    if(z == tab[a][b])
                        tab_value[tab[a][b]-1]=1;
                }
            }
            else{
                for(short b=x1  ; b <= j ; b++){
                    if(z == tab[a][b])
                        tab_value[tab[a][b]-1]=1;
                }
            }
        }
        // LECTURE COLONNE
        for(short a=0 ; a < i ; a++){
            if(z == tab[a][j])
                tab_value[tab[a][j]-1]=1;
        }
        // LECTURE LIGNE
        for(short a=0 ; a < j ; a++){
            if(z == tab[i][a])
                tab_value[tab[i][a]-1]=1;
        }
    }
    return_value.nb=0;
    /*
    return_value.val_restante = malloc(size*sizeof(short));
     */
    for(short z=0; z<size; z++){
        if(tab_value[z]==0){
            return_value.val_restante[return_value.nb]=z+1;
            return_value.nb++;
        }
    }
    return return_value;
}

BOOL check_lign(short **tab, short i, short j, short tirrage){
    for(short a=0 ; a < i ; a++){
        if(tirrage == tab[a][j])
            return FALSE;
    }
    return TRUE;
}

BOOL check_col(short **tab, short i, short j, short tirrage){
    for(short a=0 ; a < j ; a++){
        if(tirrage == tab[i][a])
            return FALSE;
    }
    return TRUE;
}

BOOL check_case(short **tab, short i, short j, short tirrage, short size){
    short x1, y1;

    y1=(short)(i-i%(short)sqrt(size));
    x1=(short)(j-j%(short)sqrt(size));
    for(short a= y1 ; a < i ; a++){
        if(a!=i){
            for(short b=x1 ; b < x1+3 ; b++){
                if(tirrage == tab[a][b])
                    return FALSE;
            }
        }
        else{
            for(short b=x1  ; b <= j ; b++){
                if(tirrage == tab[a][b])
                    return FALSE;
            }
        }
    }
    return TRUE;
}

void create_sudoku(short **tab, short size){
    value test;
    short random, val;
    srand(time(NULL));
    for(short i=0 ; i < size ; i++){
        for(short j=0 ; j < size ; j++){
            do{
                //read_sudoku(size);
                //printf("----------------------------------------\n");
                test=get_value(tab,i,j,size);
                if(test.nb==0){
                    for(short a=0 ; a<j ; a++)
                        tab[i][a]=0;
                    j=-1;
                }
                else{
                    random=(short)rand();
                    random=random%(test.nb);
                    val=test.val_restante[random];
                    tab[i][j]=val;
                }
            }
            while( j!=-1 && (check_case(tab,i,j,val,size)==FALSE || check_lign(tab,i,j,val)==FALSE || check_col(tab,i,j,val)==FALSE) );
        }
    }
}

void blank_space(short **tab, short nb_blank, short size){
    short taille = size*size;
    short random, val;
    short *tab1, *tab2;

    tab1 = malloc(sizeof(short )*taille);
    tab2 = malloc(sizeof(short)*taille);

    for(short i=0 ; i<nb_blank ; i++){
        taille = 0;
        for(short z=0 ; z<size*size ; z++){
            if(tab1[z]!=1){
                tab2[taille++]=z;
            }
        }
        random=(short)rand();
        random=random%(taille);
        val = tab2[random];
        tab1[val]=1;
        tab[val/9][val%9]=0;
    }
}

int main() {
    short **tab;

    tab=malloc(SIZE*sizeof(short *));
    for(short i=0 ; i<SIZE ;i++){
        tab[i]=malloc(SIZE*sizeof(short));
    }

    printf("Hello, World!\n");
    init_sudoku(tab,SIZE);
    create_sudoku(tab,SIZE);
    read_sudoku(tab,SIZE);
    blank_space(tab,31,SIZE);
    read_sudoku(tab,SIZE);
    return 0;
}
