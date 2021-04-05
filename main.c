#include "include/sudokuFunction.h"
#include "include/SudokuGraphic.h"
#define SIZE_SUDOKU 9

#ifndef LINUX
    int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevIns, LPSTR lpszArgument, int iShow)
    {
        Screen_type *ecran;
        SDL_Event *event = malloc(sizeof(union SDL_Event));
        SDL_bool program_lauched = SDL_TRUE;
        int newTime, oldTime;

        ecran = malloc(sizeof(Screen_type));

        if(SDL_Init(SDL_INIT_VIDEO) != 0)  // initialisation de la SDL
        {
            SDL_Log("Erreur d'initialisation de la SDL : %s", SDL_GetError());
            exit(EXIT_FAILURE);
        }

        if(TTF_Init() == -1)
        {
            SDL_Quit();
            SDL_Log( "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
            exit(EXIT_FAILURE);
        }

        //create_sudoku(sudokuNBV,sudokuNB,SIZE_SUDOKU,50); // 54 cases vide sudoku trouvé

        SDL_ShowCursor(SDL_DISABLE);
        init_Screen_type(ecran);
        charger_Accueil(ecran);
        pageAccueil(ecran);
        SDL_RenderPresent(ecran->fond);

        oldTime = SDL_GetTicks();
        while(program_lauched){

            while(SDL_PollEvent(event)){
                switch(event->type){
                    case SDL_QUIT:
                        program_lauched = SDL_FALSE;
                        break;
                    case SDL_MOUSEMOTION:
                        //SDL_Log("SIZE: %s",getSize(ecran->size));
                        //SDL_Log("test x:%d  y:%d",event->button.x,event->button.y);
                        pageAccueil(ecran);
                        cursorFormat(ecran,event->button.x,event->button.y);
                        SDL_RenderPresent(ecran->fond);
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        //SDL_Log("test x:%d  y:%d",event->button.x,event->button.y);
                        pageAction(ecran,event->button.x,event->button.y);

                        cursorFormat(ecran,event->button.x,event->button.y);
                        SDL_RenderPresent(ecran->fond);
                        break;
                    case SDL_MOUSEBUTTONUP:
                        //SDL_Log("test x:%d  y:%d",event->button.x,event->button.y);
                        ecran->drag=FALSE;
                        break;
                    case SDL_WINDOWEVENT:
                        switch (event->window.event) {
                            case SDL_WINDOWEVENT_RESIZED:
                            case SDL_WINDOWEVENT_SHOWN:
                            case SDL_WINDOWEVENT_MAXIMIZED:
                                //SDL_Log("TEST 3\n");
                                switch(ecran->p){
                                    case ACCUEIL:
                                        pageAccueil(ecran);
                                        SDL_RenderPresent(ecran->fond);
                                        break;
                                    case JEU:
                                        break;
                                    default:
                                        break;
                                }
                                //Draw_Grid_Sudoku(fond,SIZE_SUDOKU,NOIR,BLANC,NOIR,sudokuNBV);
                                break;
                            case SDL_WINDOWEVENT_MINIMIZED:
                                //SDL_Log("TEST 2\n");
                                //SDL_RenderClear(fond);
                                break;
                        }
                    default:
                        break;
                }
                newTime = SDL_GetTicks();
                if (newTime - oldTime < FPS)
                    SDL_Delay(FPS - (newTime - oldTime));
                oldTime = SDL_GetTicks();
            }
        }


        //SDL_Delay(6000);
        destroy_Screen_type(ecran);
        TTF_Quit();
        SDL_Quit();  //on quitte la SDL

        //printf("Hello word 2\n");
        return 0;
    }
#else
    int main(int argc, char *argv[]) {
    #ifdef SUDOKU
        short **tab, **tab_full;

        tab=malloc(SIZE*sizeof(short *));
        tab_full=malloc(SIZE*sizeof(short *));
        for(short i=0 ; i<SIZE ;i++){
            tab[i]=malloc(SIZE*sizeof(short));
            tab_full[i]=malloc(SIZE*sizeof(short));
        }

        printf("Hello, World!\n");
        create_sudoku(tab,tab_full,SIZE_SUDOKU,54); // 54 cases vide sudoku trouvé
        read_sudoku(tab_full,SIZE_SUDOKU);
        read_sudoku(tab,SIZE_SUDOKU);
        return 0;
    #else
        SDL_Init(SDL_INIT_VIDEO);
        SDL_Quit();
        return 0;
    #endif
    }
#endif