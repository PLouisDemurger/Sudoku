//
// Created by Pierre-Louis Demurger on 28/03/2021.
//

#ifndef SUDOKU_SUDOKUGRAPHIC_H
    #define SUDOKU_SUDOKUGRAPHIC_H
    #include <windows.h>
    #include <SDL.h>
    #include <SDL_ttf.h>
    #include <SDL_image.h>

    #define FPS (1000 / 120)
    #define BarreMinX 48
    #define BarreMaxX 632
    #define S4_4Max 12
    #define S9_9Max 50
    #define S16_16Max 50


    typedef enum{
        ROUGE,
        BLEU,
        NOIR,
        BLANC,
        VERT
    }Dcouleur;

    typedef enum{
        ACCUEIL,
        JEU
    }Page;

    typedef enum{
        QUATRExQUATRE = 4,
        NEUFxNEUF = 9,
        SEIZExSEIZE = 16
    }TailleS;

    typedef enum{
        FACILE,
        MOYEN,
        DIFFICILE
    }DifficulteS;

    typedef enum{
        NORMAL,
        CLICK,
        DRAG
    }Etat_Souris;

    typedef struct{
        short **sudoku;
        short **sudokuC;
        short NBV;
        short size;
    }Sudoku_t;

    typedef struct{
        SDL_Texture *fond;
        SDL_Texture *bouton;
        SDL_Texture *image;
        SDL_Texture *jouer;
        SDL_Texture *barre;
        SDL_Texture *pourcentageT;
        SDL_Texture *pourcentageMin;
        SDL_Texture *pourcentageMax;
        SDL_Texture *caseT;
        SDL_Texture *caseMin1;
        SDL_Texture *caseMin2;
        SDL_Texture *caseMin3;
        SDL_Texture *caseMax1;
        SDL_Texture *caseMax2;
        SDL_Texture *caseMax3;
        short x;
    } accueil_t;

    typedef struct{
        SDL_Texture *fond;
        SDL_Texture *boutonCrayon1;
        SDL_Texture *boutonCrayon2;
        SDL_Texture *chiffre;
    } jeu_t;

    typedef struct{
        SDL_Texture *cursor;
        SDL_Texture *cursorClick;
        SDL_Texture *cursorDrag;
    }souris_t;

    typedef struct{
        SDL_Window *fenetre;
        SDL_Renderer *fond;
        void *page;
        souris_t souris;
        Sudoku_t sudoku;
        DifficulteS dif;
        TailleS size;
        Page p;
        Dcouleur colorG;
        Dcouleur colorR;
        Dcouleur colorT;
        MINE_BOOLEAN drag;
        TTF_Font *police1;
        TTF_Font *police2;
    }Screen_type;

    void Draw_Grid_Sudoku(Screen_type *ecran, Sudoku_t sudoku);
    char * getSize(TailleS s);
    void pageAction(Screen_type *ecran, short x, short y);
    void cursorFormat(Screen_type *ecran, short x, short y);
    void pageAccueil(Screen_type *ecran);
    void charger_Accueil(Screen_type *ecran);
    void charger_Jeu(Screen_type *ecran);
    void init_Screen_type(Screen_type *ecran);
    void destroy_Screen_type(Screen_type *ecran);
    void destroy_Accueil(Screen_type *ecran);
    void destroy_Jeu(Screen_type *ecran);

#endif //SUDOKU_SUDOKUGRAPHIC_H
