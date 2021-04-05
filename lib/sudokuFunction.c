//
// Created by Pierre-Louis Demurger on 23/03/2021.
//
#include "../include/sudokuFunction.h"

int rdtsc()
{
    __asm__ __volatile__("rdtsc");
}

void init_sudoku(short **tab, short size){

    tab=malloc(size*sizeof(short *));
    for(short i=0 ; i<size ;i++){
        tab[i]=malloc(size*sizeof(short));
    }

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
    printf("+++++++++++++++++++++++++++++++++++++\n");
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
                for(short b=x1 ; b < x1+(short)sqrt(size) ; b++){
                    if(z == tab[a][b])
                        tab_value[z-1]=1;
                }
            }
            else{
                for(short b=x1  ; b <= j ; b++){
                    if(z == tab[a][b])
                        tab_value[z-1]=1;
                }
            }
        }
        // LECTURE COLONNE
        for(short a=0 ; a < i ; a++){
            if(z == tab[a][j])
                tab_value[z-1]=1;
        }
        // LECTURE LIGNE
        for(short a=0 ; a < j ; a++){
            if(z == tab[i][a])
                tab_value[z-1]=1;
        }
    }
    return_value.nb=0;

    for(short z=0; z<size; z++){
        if(tab_value[z]==0){
            return_value.val_restante[return_value.nb]=z+1;
            return_value.nb++;
        }
    }
    return return_value;
}

value get_value_2(short **tab, short i, short j, short size){
    short tab_value[size];
    short x1, y1;
    value return_value;

    return_value.nb=0;
    return_value.val_restante = malloc(sizeof(short)*size);
    for(short z=0; z<size; z++){
        tab_value[z]=0;
        return_value.val_restante[z]=-1;
    }
    for(short z=1; z<=size; z++){
        y1=(short)(i-i%(short)sqrt(size));
        x1=(short)(j-j%(short)sqrt(size));
        // LECTURE CASE
        for(short a=y1  ; a < y1+(short)sqrt(size) ; a++){
            for(short b=x1 ; b < x1+(short)sqrt(size) ; b++){
                if(z == tab[a][b])
                    tab_value[z-1]=1;
            }
        }
        // LECTURE COLONNE ET LIGNE
        for(short a=0 ; a < size ; a++){
            if(z == tab[a][j] || z == tab[i][a])
                tab_value[z-1]=1;
        }
    }
    return_value.nb=0;
    for(short z=0; z<size; z++){
        if(tab_value[z]==0){
            return_value.val_restante[return_value.nb++]=z+1;
        }
    }
    return return_value;
}

value get_value_3(short **tab, short i, short j, short size){
    short tab_value[size];
    short x1, y1;
    value return_value;

    return_value.nb=0;
    return_value.val_restante = malloc(sizeof(short)*size);
    for(short z=0; z<size; z++){
        tab_value[z]=0;
        return_value.val_restante[z]=-1;
    }
    for(short z=1; z<=size; z++){
        y1=(short)(i-i%(short)sqrt(size));
        x1=(short)(j-j%(short)sqrt(size));
        // LECTURE CASE
        for(short a=y1  ; a < y1+(short)sqrt(size) ; a++){
            for(short b=x1 ; b < x1+(short)sqrt(size) ; b++){
                if(z == tab[a][b])
                    tab_value[z-1]=1;
            }
        }
        // LECTURE COLONNE ET LIGNE
        for(short a=0 ; a < size ; a++){
            if(z == tab[a][j] || z == tab[i][a])
                tab_value[z-1]=1;
        }
    }
    return_value.nb=0;
    for(short z=0; z<size; z++){
        return_value.val_restante[return_value.nb++]=tab_value[z];
    }
    return return_value;
}

MINE_BOOLEAN check_lign(short **tab, short i, short j, short tirrage){
    for(short a=0 ; a < i ; a++){
        if(tirrage == tab[a][j])
            return FALSE;
    }
    return TRUE;
}

MINE_BOOLEAN check_col(short **tab, short i, short j, short tirrage){
    for(short a=0 ; a < j ; a++){
        if(tirrage == tab[i][a])
            return FALSE;
    }
    return TRUE;
}

MINE_BOOLEAN check_case(short **tab, short i, short j, short tirrage, short size){
    short x1, y1;

    y1=(short)(i-i%(short)sqrt(size));
    x1=(short)(j-j%(short)sqrt(size));
    for(short a= y1 ; a < i ; a++){
        if(a!=i){
            for(short b=x1 ; b < x1+(short)sqrt(size) ; b++){
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

void create_sudoku_grid(short **tab, short size){
    value test;
    short random, val;
    srand(time(NULL));
    for(short i=0 ; i < size ; i++){
        for(short j=0 ; j < size ; j++){
            do{
                test=get_value(tab,i,j,size);
                if(test.nb==0){
                    for(short a=0 ; a<=j ; a++)
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

    srand(rdtsc());

    tab1 = malloc(sizeof(short)*taille);
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
        tab[val/size][val%size]=0;
    }
}

short no_zero(short **tab, short size){
    short nb=0;
    for(short i=0 ; i<size ; i++){
        for(short j=0 ; j<size ; j++){
            if(tab[i][j]==0)
                nb++;
        }
    }
    return nb;
};

MINE_BOOLEAN resolve_sudoku(short **tab, short size){
    short **tabTest;
    short repetition, old_value, new_value;
    value val;

    repetition=0;
    old_value=-1;

    tabTest=malloc(size*sizeof(short *));
    for(short i=0 ; i<size ; i++) {
        tabTest[i]=malloc(size*sizeof(short));
    }

    for(short i=0 ; i<size ; i++) {
        for (short j = 0; j < size; j++) {
            tabTest[i][j]=tab[i][j];
        }
    }

    do{
        for(short i=0 ; i<size ; i++){
            for(short j=0 ; j<size ; j++){
                if(tabTest[i][j]==0){
                    val=get_value_2(tabTest,i,j,size);
                    if(val.nb==1){
                        //printf("value=%hd | x=%hd | y=%hd\n",val.val_restante[0],j,i);
                        tabTest[i][j]=val.val_restante[0];
                        //read_sudoku(tabTest,size);
                    }
                }
            }
        }
        new_value=no_zero(tabTest,size);
        if(old_value==new_value){
            repetition++;
        }
        else{
            old_value=new_value;
            repetition=0;
        }
    }
    while(new_value!=0 && repetition<=10);
    if(new_value==0)
        return TRUE;
    else {
        //read_sudoku(tabTest,size);
        return FALSE;
    }
}

MINE_BOOLEAN resolve_sudoku_2(short **tab, short size){
    short **tabTest, **nb_maquant;
    short x1, y1, racine, test, x, y, cases;
    short repetition, old_value, new_value;
    value val;

    repetition=0;
    old_value=-1;
    racine=(short)sqrt(size);

    tabTest=malloc(size*sizeof(short *));
    nb_maquant=malloc(size*sizeof(short *));
    for(short i=0 ; i<size ; i++) {
        tabTest[i]=malloc(size*sizeof(short));
        nb_maquant[i]=malloc(size*sizeof(short));
    }

    for(short i=0 ; i<size ; i++) {
        for (short j = 0; j < size; j++) {
            tabTest[i][j]=tab[i][j];
            nb_maquant[i][j]=-1;
        }
    }

    do{
        for(short i=0 ; i<size ; i++){
            for(short j=0 ; j<size ; j++){
                if(tabTest[i][j]==0){
                    val=get_value_2(tabTest,i,j,size);
                    if(val.nb==1){
                        //printf("value=%hd | x=%hd | y=%hd\n",val.val_restante[0],j,i);
                        tabTest[i][j]=val.val_restante[0];
                        //read_sudoku(tabTest,size);
                    }
                }
            }
        }
        for(short i=0 ; i<size ; i++){
            cases=0;
            x1=(short)(i%racine);
            y1=(short)(i/racine);
            for(short j=x1*racine ; j<(x1+1)*racine ; j++){
                for(short k=y1*racine ; k<(y1+1)*racine ; k++) {
                    if (tabTest[k][j] == 0) {
                        val = get_value_3(tabTest, i, j, size);
                        for(short l=0 ; l<size ; l++) {
                            nb_maquant[cases][l] = val.val_restante[l];
                        }
                    }
                    else{
                        for(short l=0 ; l<size ; l++) {
                            nb_maquant[cases][l] = -1;
                        }
                    }
                    cases++;
                }
            }
            for(short l=0 ; l<size ; l++) {
                test=0;
                for (short j = 0; j < size; j++) {
                    if (nb_maquant[j][l] == -1){
                        break;
                    }
                    else if (nb_maquant[j][l] == 0){
                        test++;
                        x=x1*racine+(short)(j%racine);
                        y=y1*racine+(short)(j/racine);
                    }
                }
                if(test==1){
                    //printf("value=%hd | x=%hd | y=%hd\n",l,x,y);
                    tabTest[y][x]=l;
                    //read_sudoku(tabTest,size);
                }
            }
        }
        new_value=no_zero(tabTest,size);
        if(old_value==new_value){
            repetition++;
        }
        else{
            old_value=new_value;
            repetition=0;
        }
    }
    while(new_value!=0 && repetition<=10);
    if(new_value==0)
        return TRUE;
    else {
        //read_sudoku(tabTest,size);
        return FALSE;
    }
}

void init_test_sudoku(short **tab){
    tab[0][0]=6;tab[0][1]=8;tab[0][2]=4;tab[0][3]=1;tab[0][4]=0;tab[0][5]=3;tab[0][6]=5;tab[0][7]=7;tab[0][8]=0;
    tab[1][0]=7;tab[1][1]=5;tab[1][2]=0;tab[1][3]=4;tab[1][4]=6;tab[1][5]=8;tab[1][6]=3;tab[1][7]=2;tab[1][8]=1;
    tab[2][0]=0;tab[2][1]=2;tab[2][2]=1;tab[2][3]=0;tab[2][4]=0;tab[2][5]=0;tab[2][6]=0;tab[2][7]=8;tab[2][8]=4;
    tab[3][0]=8;tab[3][1]=0;tab[3][2]=0;tab[3][3]=0;tab[3][4]=3;tab[3][5]=6;tab[3][6]=9;tab[3][7]=0;tab[3][8]=0;
    tab[4][0]=0;tab[4][1]=6;tab[4][2]=7;tab[4][3]=9;tab[4][4]=0;tab[4][5]=4;tab[4][6]=1;tab[4][7]=3;tab[4][8]=8;
    tab[5][0]=4;tab[5][1]=0;tab[5][2]=0;tab[5][3]=0;tab[5][4]=1;tab[5][5]=7;tab[5][6]=2;tab[5][7]=0;tab[5][8]=0;
    tab[6][0]=5;tab[6][1]=0;tab[6][2]=0;tab[6][3]=0;tab[6][4]=0;tab[6][5]=9;tab[6][6]=8;tab[6][7]=0;tab[6][8]=3;
    tab[7][0]=1;tab[7][1]=3;tab[7][2]=8;tab[7][3]=0;tab[7][4]=7;tab[7][5]=0;tab[7][6]=0;tab[7][7]=9;tab[7][8]=6;
    tab[8][0]=9;tab[8][1]=4;tab[8][2]=6;tab[8][3]=3;tab[8][4]=0;tab[8][5]=0;tab[8][6]=7;tab[8][7]=5;tab[8][8]=0;
}

void copy_sudoku(short **sudoku1, short **sudoku2, short size){
    for(short i=0 ; i<size ; i++) {
        for (short j = 0; j < size; j++) {
            sudoku2[i][j] = sudoku1[i][j];
        }
    }
}

void create_sudoku(short **sudoku, short **sudoku_full, short size, short empty){
    init_sudoku(sudoku,size);
    init_sudoku(sudoku_full,size);
    create_sudoku_grid(sudoku,size);
    copy_sudoku(sudoku,sudoku_full,size);
    do{
#ifdef DEBUG
        init_test_sudoku(tab);
        read_sudoku(tab,size);
#else
        copy_sudoku(sudoku_full,sudoku,size);
        blank_space(sudoku,empty,size);
        //printf("\n\n#########################################\n\n");
        //read_sudoku(sudoku,size);
#endif
    }
    while(resolve_sudoku_2(sudoku,size)==FALSE);
}


