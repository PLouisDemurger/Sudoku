//
// Created by Pierre-Louis Demurger on 28/03/2021.
//

#include "../include/sudokuFunction.h"
#include "../include/SudokuGraphic.h"

char * getSize(TailleS s){
    switch (s) {
        case QUATRExQUATRE:
            return "4x4";
        case SEIZExSEIZE:
            return "16x16";
        case NEUFxNEUF:
            return "9x9";
        default:
            return "";
    }
}

void changeAccueil_Texte(Screen_type *ecran){
    accueil_t *Accueil = ecran->page;
    SDL_Surface *image;
    SDL_Color colorTexte;
    char texte[40];
    short pourcentage, t;

    SDL_DestroyTexture(Accueil->pourcentageT);
    SDL_DestroyTexture(Accueil->caseT);

    /**
     * NB pourcentageT
     */
    pourcentage = (Accueil->x-BarreMinX)*100/(BarreMaxX-BarreMinX);
    sprintf(texte,"%hd",pourcentage);
    strcat(texte,"%\0");
    image = TTF_RenderText_Blended(ecran->police1,texte, colorTexte);
    if(image==NULL)
        SDL_Log("Problème de texte");
    Accueil->pourcentageT = SDL_CreateTextureFromSurface(ecran->fond,image);
    SDL_FreeSurface(image);
    if(Accueil->pourcentageT==NULL)
        SDL_Log("Problème de chargement pourcentageT Accueil");

    /**
     * NB caseT
     */
    switch(ecran->size){
        case QUATRExQUATRE:
            t=S4_4Max;
            break;
        case NEUFxNEUF:
            t=S9_9Max;
            break;
        case SEIZExSEIZE:
            t=S16_16Max;
            break;
        default:
            t=0;
            break;
    }
    pourcentage = pourcentage*t/100;
    ecran->sudoku.NBV=pourcentage;
    sprintf(texte,"%hd",pourcentage);
    image = TTF_RenderText_Blended(ecran->police1,texte, colorTexte);
    if(image==NULL)
        SDL_Log("Problème de texte");
    Accueil->caseT = SDL_CreateTextureFromSurface(ecran->fond,image);
    SDL_FreeSurface(image);
    if(Accueil->caseT==NULL)
        SDL_Log("Problème de chargement pourcentageT Accueil");
}

void afficher_bouton(Screen_type *ecran, SDL_Texture *text, SDL_Rect rectangle){
    if(SDL_QueryTexture(text,NULL,NULL,&rectangle.w,&rectangle.h)!=0)
        SDL_Log("Problème de chargement image 2");
    if(SDL_RenderCopy(ecran->fond,text,NULL,&rectangle)!=0)
        SDL_Log("Problème de chargement image 3");
}

void pageAccueil(Screen_type *ecran){
    //SDL_Log("TEST");
    accueil_t *Accueil;
    SDL_Rect rectangle;

    Accueil=ecran->page;
    //SDL_RenderClear(ecran->fond);
    //SDL_Log("CLEAR\n");

    rectangle.x=0;
    rectangle.y=0;
    afficher_bouton(ecran,Accueil->fond,rectangle);

    switch (ecran->size) {
        case QUATRExQUATRE:
            rectangle.x=155;
            rectangle.y=175;
            afficher_bouton(ecran,Accueil->image,rectangle);
            rectangle.x=158;
            rectangle.y=297;
            afficher_bouton(ecran,Accueil->bouton,rectangle);
            rectangle.x=33;
            rectangle.y=455; // 461
            afficher_bouton(ecran,Accueil->caseMin1,rectangle);
            rectangle.x=627;
            rectangle.y=455;
            afficher_bouton(ecran,Accueil->caseMax1,rectangle);
            //SDL_Log("SIZE: 4x4 s");
            //SDL_Log("----------------------");
            break;
        case NEUFxNEUF:
            rectangle.x=290;
            rectangle.y=175;
            afficher_bouton(ecran,Accueil->image,rectangle);
            rectangle.x=292;
            rectangle.y=297;
            afficher_bouton(ecran,Accueil->bouton,rectangle);
            rectangle.x=33;
            rectangle.y=455; // 461
            afficher_bouton(ecran,Accueil->caseMin2,rectangle);
            rectangle.x=627;
            rectangle.y=455;
            afficher_bouton(ecran,Accueil->caseMax2,rectangle);
            //SDL_Log("SIZE: 9x9 s");
            //SDL_Log("----------------------");
            break;
        case SEIZExSEIZE:
            rectangle.x=425;
            rectangle.y=175;
            afficher_bouton(ecran,Accueil->image,rectangle);
            rectangle.x=428;
            rectangle.y=297;
            afficher_bouton(ecran,Accueil->bouton,rectangle);
            rectangle.x=33;
            rectangle.y=455; // 461
            afficher_bouton(ecran,Accueil->caseMin3,rectangle);
            rectangle.x=627;
            rectangle.y=455;
            afficher_bouton(ecran,Accueil->caseMax3,rectangle);
            //SDL_Log("SIZE: 16x16 s");
            //SDL_Log("----------------------");
            break;
        default:
            break;
    }
    rectangle.x=30;
    rectangle.y=415; // 461
    afficher_bouton(ecran,Accueil->pourcentageMin,rectangle);
    rectangle.x=620;
    rectangle.y=415;
    afficher_bouton(ecran,Accueil->pourcentageMax,rectangle);
    rectangle.x=341;
    rectangle.y=415; // 461
    afficher_bouton(ecran,Accueil->pourcentageT,rectangle);
    rectangle.x=341;
    rectangle.y=455;
    afficher_bouton(ecran,Accueil->caseT,rectangle);
    rectangle.x=Accueil->x-3;
    rectangle.y=439;
    afficher_bouton(ecran,Accueil->barre,rectangle);

    if(ecran->p == JEU){
        rectangle.x=209;
        rectangle.y=514;
        afficher_bouton(ecran,Accueil->jouer,rectangle);
        //destroy_Accueil(ecran);
        //charger_Jeu(ecran);
    }
}

void pageAction(Screen_type *ecran, short x, short y){
    accueil_t *a;

    switch (ecran->p) {
        case ACCUEIL:
            a=ecran->page;
            if((y>=175 && y<=275) || (y>=297 && y<=335)){
                if( (x>=158 && x<=252) || (x>=155 && x<=255) ){ // w = 94 h = 38
                    ecran->sudoku.size=4;
                    ecran->size=QUATRExQUATRE;
                }
                else if( (x>=292 && x<=386) || (x>=290 && x<=390) ){
                    ecran->sudoku.size=9;
                    ecran->size=NEUFxNEUF;
                }
                else if( (x>=425 && x<=525) || (x>=428 && x<=522) ){
                    ecran->sudoku.size=16;
                    ecran->size=SEIZExSEIZE;
                }
                changeAccueil_Texte(ecran);
            }
            else if((y>=436 && y<=457) && ((x>=a->x-3) && (x<=a->x+3)) && ecran->drag==FALSE){
                ecran->drag = TRUE;
            }
            else if((y>=514 && y<=573) && ((x>=209) && (x<=471)) && ecran->drag==FALSE){
                create_sudoku(ecran->sudoku.sudoku,ecran->sudoku.sudokuC,ecran->sudoku.size,ecran->sudoku.NBV);
                ecran->p = JEU;
            }
            pageAccueil(ecran);
            break;
        case JEU:

            break;
        default:
            break;
    }
}

void cursorImage(Screen_type *s, Etat_Souris e, short x, short y){
    SDL_Rect rectangle, r2;
    SDL_Texture *text, *t1, *t2;

    rectangle.x=x-8;
    r2.x=-30;
    rectangle.y=y;
    r2.y=-30;
    rectangle.w=25;
    r2.w=25;
    rectangle.h=25;
    r2.h=25;
    switch (e) {
        case NORMAL:
            text = s->souris.cursor;
            t1 = s->souris.cursorClick;
            t2 = s->souris.cursorDrag;
            break;
        case CLICK:
            text = s->souris.cursorClick;
            t1 = s->souris.cursor;
            t2 = s->souris.cursorDrag;
            break;
        case DRAG:
            text = s->souris.cursorDrag;
            t1 = s->souris.cursorClick;
            t2 = s->souris.cursor;
            break;
        default:
            text = NULL;
            break;
    }

    if(SDL_RenderCopy(s->fond,text,NULL,&rectangle)!=0)
        SDL_Log("Problème de chargement image 3_2");

    if(SDL_RenderCopy(s->fond,t1,NULL,&r2)!=0)
        SDL_Log("Problème de chargement image 3_2");
    if(SDL_RenderCopy(s->fond,t2,NULL,&r2)!=0)
        SDL_Log("Problème de chargement image 3_2");

    //SDL_RenderPresent(s->fond);
}

void cursorFormat(Screen_type *ecran, short x, short y){
    accueil_t *a;
    switch(ecran->p){
        case ACCUEIL:
            a = ecran->page;
            if( ( ((y>=175 && y<=275) || (y>=297 && y<=335))
                && ( (x>=158 && x<=252) || (x>=292 && x<=386) || (x>=428 && x<=522)
                || (x>=425 && x<=525) || (x>=290 && x<=390) || (x>=155 && x<=255) ) ) ) {
                cursorImage(ecran,CLICK,x,y);
            }
            else if( (y>=436 && y<=457) && ((x>=a->x-3) && (x<=a->x+3)) && ecran->drag==FALSE){
                cursorImage(ecran,CLICK,x,y);
            }
            else if((y>=436 && y<=457) && ((x>=BarreMinX) && (x<=BarreMaxX)) && ecran->drag==TRUE){
                cursorImage(ecran,DRAG,x,y);
                a->x = x;
                changeAccueil_Texte(ecran);
            }
            else{
                cursorImage(ecran,NORMAL,x,y);
                ecran->drag = FALSE;
            }
            break;
        case JEU:
            break;
        default:
            SDL_ShowCursor(SDL_ENABLE);
            break;
    }
}

void init_Screen_type(Screen_type *ecran){
    SDL_Surface *image;
    ecran->p = ACCUEIL;
    ecran->size = NEUFxNEUF;
    ecran->sudoku.size=9;
    ecran->sudoku.NBV=25;

    ecran->drag = FALSE;

    ecran->fenetre = SDL_CreateWindow("Une fenetre SDL",
                                      SDL_WINDOWPOS_CENTERED,
                                      SDL_WINDOWPOS_CENTERED, 680, 680, SDL_WINDOW_RESIZABLE);  // Création de la fenêtre

    SDL_SetWindowMaximumSize(ecran->fenetre,680,680);

    if (ecran->fenetre == NULL)  //gestion des erreurs
    {
        SDL_Log("Erreur lors de la creation d'une fenetre : %s", SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    ecran->fond = SDL_CreateRenderer(ecran->fenetre,1,SDL_RENDERER_ACCELERATED);

    if (ecran->fond == NULL)  //gestion des erreurs
    {
        SDL_Log("Erreur lors de la creation du fond : %s", SDL_GetError());
        //SDL_DestroyWindow(fenetre);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    /**
     * normal_cursor
     */
    //SDL_Log("nom: %s",name);
    image=IMG_Load("Image/Cursor/normal_cursor.png");
    if(image==NULL)
        SDL_Log("L'image n'a pas été chargé");

    ecran->souris.cursor = SDL_CreateTextureFromSurface(ecran->fond,image);
    SDL_FreeSurface(image);
    if(ecran->souris.cursor==NULL)
        SDL_Log("Problème de chargement normal_cursor");

    /**
     * cursorClick
     */
    image=IMG_Load("Image/Cursor/click_cursor.png");
    if(image==NULL)
        SDL_Log("L'image n'a pas été chargé");

    ecran->souris.cursorClick = SDL_CreateTextureFromSurface(ecran->fond,image);
    SDL_FreeSurface(image);
    if(ecran->souris.cursorClick==NULL)
        SDL_Log("Problème de chargement cursorClick");

    /**
     * cursorDrag
     */
    image=IMG_Load("Image/Cursor/drag_cursor.png");
    if(image==NULL)
        SDL_Log("L'image n'a pas été chargé");

    ecran->souris.cursorDrag = SDL_CreateTextureFromSurface(ecran->fond,image);
    SDL_FreeSurface(image);
    if(ecran->souris.cursorDrag==NULL)
        SDL_Log("Problème de chargement cursorDrag");

    ecran->police1=TTF_OpenFont("Texte/Marons-Regular.ttf",20);
    if(ecran->police1==NULL)
        SDL_Log("La police n'a pas été chargé");

    ecran->police2=TTF_OpenFont("Texte/Roboto-Medium.ttf",20);
    if(ecran->police2==NULL)
        SDL_Log("La police n'a pas été chargé");
}

void destroy_Screen_type(Screen_type *ecran){
    TTF_CloseFont(ecran->police1);
    TTF_CloseFont(ecran->police2);
    SDL_DestroyRenderer(ecran->fond);
    SDL_DestroyWindow(ecran->fenetre);
    switch(ecran->p){
        case ACCUEIL:
            destroy_Accueil(ecran);
            break;
        default:
            break;
    }
}

void charger_Accueil(Screen_type *ecran){
    char texte[40];
    short pourcentage;
    accueil_t *Accueil;
    SDL_Surface *image;
    SDL_Color colorTexte;

    ecran->page = malloc(sizeof(accueil_t));
    Accueil=ecran->page;

    Accueil->x = BarreMinX + (BarreMaxX-BarreMinX)/2;

    colorTexte.r=0;
    colorTexte.b=0;
    colorTexte.g=0;

    /**
     * FOND
     */
    //SDL_Log("nom: %s",name);
    image=IMG_Load("Image/Accueil/Page_Accueil.png");
    if(image==NULL)
        SDL_Log("L'image n'a pas été chargé");

    Accueil->fond = SDL_CreateTextureFromSurface(ecran->fond,image);
    SDL_FreeSurface(image);
    if(Accueil->fond==NULL)
        SDL_Log("Problème de chargement fond Accueil");

    /**
     * JOUER
     */
    image=IMG_Load("Image/Accueil/Validation_jouer.png");
    if(image==NULL)
        SDL_Log("L'image n'a pas été chargé");

    Accueil->jouer = SDL_CreateTextureFromSurface(ecran->fond,image);
    SDL_FreeSurface(image);
    if(Accueil->jouer==NULL)
        SDL_Log("Problème de chargement jouer Accueil");

    /**
     * BARRE
     */
    image=IMG_Load("Image/Accueil/Validation_Difficulté.png");
    if(image==NULL)
        SDL_Log("L'image n'a pas été chargé");

    Accueil->barre = SDL_CreateTextureFromSurface(ecran->fond,image);
    SDL_FreeSurface(image);
    if(Accueil->barre==NULL)
        SDL_Log("Problème de chargement barre Accueil");

    /**
     * bouton
     */
    image=IMG_Load("Image/Accueil/Validation_Taille.png");
    if(image==NULL)
        SDL_Log("L'image n'a pas été chargé");

    Accueil->bouton = SDL_CreateTextureFromSurface(ecran->fond,image);
    SDL_FreeSurface(image);
    if(Accueil->bouton==NULL)
        SDL_Log("Problème de chargement bouton1 Accueil");

    /**
     * image
     */
    image=IMG_Load("Image/Accueil/Validation_Rond.png");
    if(image==NULL)
        SDL_Log("L'image n'a pas été chargé");

    Accueil->image= SDL_CreateTextureFromSurface(ecran->fond,image);
    SDL_FreeSurface(image);
    if(Accueil->image==NULL)
        SDL_Log("Problème de chargement image1 Accueil");


    /**
     * NB case vide 1 min
     */
    image = TTF_RenderText_Blended(ecran->police1, "0", colorTexte);
    if(image==NULL)
        SDL_Log("Problème de texte");
    Accueil->caseMin1 = SDL_CreateTextureFromSurface(ecran->fond,image);
    SDL_FreeSurface(image);
    if(Accueil->caseMin1==NULL)
        SDL_Log("Problème de chargement caseMin1 Accueil");

    /**
     * NB case vide 1 max
     */
    image = TTF_RenderText_Blended(ecran->police1, "12", colorTexte);
    if(image==NULL)
        SDL_Log("Problème de texte");
    Accueil->caseMax1 = SDL_CreateTextureFromSurface(ecran->fond,image);
    SDL_FreeSurface(image);
    if(Accueil->caseMax1==NULL)
        SDL_Log("Problème de chargement caseMax1 Accueil");

    /**
     * NB case vide 2 min
     */
    image = TTF_RenderText_Blended(ecran->police1, "0", colorTexte);
    if(image==NULL)
        SDL_Log("Problème de texte");
    Accueil->caseMin2 = SDL_CreateTextureFromSurface(ecran->fond,image);
    SDL_FreeSurface(image);
    if(Accueil->caseMin2==NULL)
        SDL_Log("Problème de chargement caseMin2 Accueil");

    /**
     * NB case vide 2 max
     */
    image = TTF_RenderText_Blended(ecran->police1, "50", colorTexte);
    if(image==NULL)
        SDL_Log("Problème de texte");
    Accueil->caseMax2 = SDL_CreateTextureFromSurface(ecran->fond,image);
    SDL_FreeSurface(image);
    if(Accueil->caseMax2==NULL)
        SDL_Log("Problème de chargement caseMax2 Accueil");

    /**
     * NB case vide 3 min
     */
    image = TTF_RenderText_Blended(ecran->police1, "0", colorTexte);
    if(image==NULL)
        SDL_Log("Problème de texte");
    Accueil->caseMin3 = SDL_CreateTextureFromSurface(ecran->fond,image);
    SDL_FreeSurface(image);
    if(Accueil->caseMin3==NULL)
        SDL_Log("Problème de chargement caseMin3 Accueil");

    /**
     * NB case vide 3 max
     */
    image = TTF_RenderText_Blended(ecran->police1, "50", colorTexte);
    if(image==NULL)
        SDL_Log("Problème de texte");
    Accueil->caseMax3 = SDL_CreateTextureFromSurface(ecran->fond,image);
    SDL_FreeSurface(image);
    if(Accueil->caseMax3==NULL)
        SDL_Log("Problème de chargement caseMax3 Accueil");

    /**
     * NB pourcentage vide min
     */
    image = TTF_RenderText_Blended(ecran->police1, "0%", colorTexte);
    if(image==NULL)
        SDL_Log("Problème de texte");
    Accueil->pourcentageMin = SDL_CreateTextureFromSurface(ecran->fond,image);
    SDL_FreeSurface(image);
    if(Accueil->pourcentageMin==NULL)
        SDL_Log("Problème de chargement pourcentageMin Accueil");

    /**
     * NB pourcentage vide max
     */
    image = TTF_RenderText_Blended(ecran->police1, "100%", colorTexte);
    if(image==NULL)
        SDL_Log("Problème de texte");
    Accueil->pourcentageMax = SDL_CreateTextureFromSurface(ecran->fond,image);
    SDL_FreeSurface(image);
    if(Accueil->pourcentageMax==NULL)
        SDL_Log("Problème de chargement pourcentageMax Accueil");

    /**
     * NB pourcentageT
     */
    pourcentage = (Accueil->x-BarreMinX)*100/(BarreMaxX-BarreMinX);
    sprintf(texte,"%hd",pourcentage);
    strcat(texte,"%\0");
    image = TTF_RenderText_Blended(ecran->police1,texte, colorTexte);
    if(image==NULL)
        SDL_Log("Problème de texte");
    Accueil->pourcentageT = SDL_CreateTextureFromSurface(ecran->fond,image);
    SDL_FreeSurface(image);
    if(Accueil->pourcentageT==NULL)
        SDL_Log("Problème de chargement pourcentageT Accueil");

    /**
     * NB caseT
     */
    pourcentage = pourcentage*S9_9Max/100;
    sprintf(texte,"%hd",pourcentage);
    image = TTF_RenderText_Blended(ecran->police1,texte, colorTexte);
    if(image==NULL)
        SDL_Log("Problème de texte");
    Accueil->caseT = SDL_CreateTextureFromSurface(ecran->fond,image);
    SDL_FreeSurface(image);
    if(Accueil->caseT==NULL)
        SDL_Log("Problème de chargement pourcentageT Accueil");
}

void destroy_Accueil(Screen_type *ecran){
    accueil_t *Accueil=ecran->page;


    /**
     * FOND
     */
    SDL_DestroyTexture(Accueil->fond);

    /**
     * BARRE
     */
    SDL_DestroyTexture(Accueil->barre);

    /**
     * bouton
     */
    SDL_DestroyTexture(Accueil->bouton);

    /**
     * image
     */
    SDL_DestroyTexture(Accueil->image);


    /**
     * NB case vide 1 min
     */
    SDL_DestroyTexture(Accueil->caseMin1);

    /**
     * NB case vide 1 max
     */
    SDL_DestroyTexture(Accueil->caseMax1);

    /**
     * NB case vide 2 min
     */
    SDL_DestroyTexture(Accueil->caseMin2);

    /**
     * NB case vide 2 max
     */
    SDL_DestroyTexture(Accueil->caseMax2);

    /**
     * NB case vide 3 min
     */
    SDL_DestroyTexture(Accueil->caseMin3);

    /**
     * NB case vide 3 max
     */
    SDL_DestroyTexture(Accueil->caseMax3);

    /**
     * NB pourcentage vide min
     */
    SDL_DestroyTexture(Accueil->pourcentageMin);

    /**
     * NB pourcentage vide max
     */
    SDL_DestroyTexture(Accueil->pourcentageMax);

    /**
     * NB pourcentageT
     */
    SDL_DestroyTexture(Accueil->pourcentageT);

    /**
     * NB caseT
     */
    SDL_DestroyTexture(Accueil->caseT);

    free(ecran->page);
}

void charger_Jeu(Screen_type *ecran){
    char texte[40];
    short pourcentage;
    jeu_t *Jeu;
    SDL_Surface *image;
    SDL_Color colorTexte;

    ecran->page = malloc(sizeof(jeu_t));
    Jeu=ecran->page;

    colorTexte.r=0;
    colorTexte.b=0;
    colorTexte.g=0;

    /**
     * FOND
     */
    //SDL_Log("nom: %s",name);
    switch (ecran->size) {
        case QUATRExQUATRE:
            image=IMG_Load("Image/Jeu/Page_Jeu_4.png");
            break;
        case NEUFxNEUF:
            image=IMG_Load("Image/Jeu/Page_Jeu_9.png");
            break;
        case SEIZExSEIZE:
            image=IMG_Load("Image/Jeu/Page_Jeu_16.png");
            break;
        default:
            image=IMG_Load("Image/Jeu/Page_Jeu_9.png");
            break;
    }
    if(image==NULL)
        SDL_Log("L'image n'a pas été chargé");

    Jeu->fond = SDL_CreateTextureFromSurface(ecran->fond,image);
    SDL_FreeSurface(image);
    if(Jeu->fond==NULL)
        SDL_Log("Problème de chargement fond Jeu");

    /**
     * boutonCrayon1
     */
    image=IMG_Load("Image/Jeu/crayonNV.png");
    if(image==NULL)
        SDL_Log("L'image n'a pas été chargé");

    Jeu->boutonCrayon1 = SDL_CreateTextureFromSurface(ecran->fond,image);
    SDL_FreeSurface(image);
    if(Jeu->boutonCrayon1==NULL)
        SDL_Log("Problème de boutonCrayon1 Jeu");

    /**
     * boutonCrayon2
     */
    image=IMG_Load("Image/Jeu/crayonV.png");
    if(image==NULL)
        SDL_Log("L'image n'a pas été chargé");

    Jeu->boutonCrayon2 = SDL_CreateTextureFromSurface(ecran->fond,image);
    SDL_FreeSurface(image);
    if(Jeu->boutonCrayon2==NULL)
        SDL_Log("Problème de boutonCrayon2 Jeu");

    /**
     * chiffre
     */
    image=IMG_Load("Image/Jeu/chiffreAction.png");
    if(image==NULL)
        SDL_Log("L'image n'a pas été chargé");

    Jeu->chiffre = SDL_CreateTextureFromSurface(ecran->fond,image);
    SDL_FreeSurface(image);
    if(Jeu->chiffre==NULL)
        SDL_Log("Problème de boutonCrayon2 Jeu");
}

void destroy_Jeu(Screen_type *ecran){
    jeu_t *Jeu=ecran->page;

    /**
     * FOND
     */
    SDL_DestroyTexture(Jeu->fond);

    /**
     * boutonCrayon1
     */
    SDL_DestroyTexture(Jeu->boutonCrayon1);

    /**
     * boutonCrayon2
     */
    SDL_DestroyTexture(Jeu->boutonCrayon2);

    /**
     * chiffre
     */
    SDL_DestroyTexture(Jeu->chiffre);

    free(ecran->page);
}



















void get_RGB_Color(Uint8 *r, Uint8 *b, Uint8 *v, Dcouleur color){
    switch(color){
        case BLANC:
            *r=255;
            *b=255;
            *v=255;
            break;
        case NOIR:
            *r=0;
            *b=0;
            *v=0;
            break;
        case ROUGE:
            *r=255;
            *b=0;
            *v=0;
            break;
        case BLEU:
            *r=0;
            *b=255;
            *v=0;
            break;
        case VERT:
            *r=0;
            *b=0;
            *v=255;
            break;
        default:
            break;
    }
}

char recupChar(short i){
    switch(i){
        case 1:
            return '1';
        case 2:
            return '2';
        case 3:
            return '3';
        case 4:
            return '4';
        case 5:
            return '5';
        case 6:
            return '6';
        case 7:
            return '7';
        case 8:
            return '8';
        case 9:
            return '9';
        case 10:
            return 'A';
        case 11:
            return 'B';
        case 12:
            return 'C';
        case 13:
            return 'D';
        case 14:
            return 'E';
        case 15:
            return 'F';
        case 16:
            return 'G';
        default:
            return ' ';
    }
}

void prepTexte(short val, short size, Uint8 i, Uint8 j, SDL_Renderer *fond, Dcouleur colorT){
    char chiffre[2];
    SDL_Rect rectangle;
    SDL_Texture *texte;
    SDL_Surface *t;
    Uint8 rouge, vert, bleu;
    SDL_Color colorTexte;
    TTF_Font *police = NULL;

    police=TTF_OpenFont("LinLibertine_R.ttf",25);
    if(police==NULL)
        SDL_Log("La police n'a pas été chargé");

    get_RGB_Color(&rouge, &bleu, &vert, colorT);

    colorTexte.r=rouge;
    colorTexte.b=bleu;
    colorTexte.g=vert;

    sprintf(chiffre,"%c",recupChar(val));
    t = TTF_RenderText_Blended(police, chiffre, colorTexte);
    if(t==NULL)
        SDL_Log("Problème de chargement  1");
    texte = SDL_CreateTextureFromSurface(fond,t);
    SDL_FreeSurface(t);
    if(t==NULL)
        SDL_Log("Problème de chargement texte 2");
    rectangle.h=40;
    rectangle.w=40;
    rectangle.x=25+j*40+(j/(int)sqrt(size));
    rectangle.y=15+i*40+(i/(int)sqrt(size));
    if(SDL_QueryTexture(texte,NULL,NULL,&rectangle.w,&rectangle.h)!=0)
        SDL_Log("Problème de chargement texte 3");
    if(SDL_RenderCopy(fond,texte,NULL,&rectangle)!=0)
        SDL_Log("Problème de chargement texte 3");
    TTF_CloseFont(police);

    rectangle.x=425;
    rectangle.y=175;
    rectangle.w=100;
    rectangle.h=100;

    rectangle.x=428;
    rectangle.y=297;
    rectangle.w=94;
    rectangle.h=38;

}

void Draw_Grid_Sudoku(Screen_type *ecran, Sudoku_t sudoku){
    SDL_Rect *rects = malloc((1+sudoku.size*sudoku.size)*sizeof(SDL_Rect));
    Uint8 rouge, vert, bleu;

    for(short i=0 ; i<sudoku.size ; i++){
        for(short j=0 ; j<sudoku.size ; j++){
            rects[i*sudoku.size+j].h=40;
            rects[i*sudoku.size+j].w=40;
            rects[i*sudoku.size+j].x=10+j*40+(int)(j/(int)sqrt(sudoku.size));
            rects[i*sudoku.size+j].y=10+i*40+(int)(i/(int)sqrt(sudoku.size));
        }
    }

    rects[sudoku.size*sudoku.size].h=40*sudoku.size+(int)sqrt(sudoku.size)+3;
    rects[sudoku.size*sudoku.size].w=40*sudoku.size+(int)sqrt(sudoku.size)+3;
    rects[sudoku.size*sudoku.size].x=8;
    rects[sudoku.size*sudoku.size].y=8;

    get_RGB_Color(&rouge, &bleu, &vert, ecran->colorR);


    if(SDL_SetRenderDrawColor(ecran->fond,rouge,vert,bleu,SDL_ALPHA_OPAQUE) != 0)
    {
        SDL_Log("Erreur lors du changement de la couleur : %s", SDL_GetError());
    }

    SDL_RenderClear(ecran->fond);

    get_RGB_Color(&rouge, &bleu, &vert, ecran->colorG);

    if(SDL_SetRenderDrawColor(ecran->fond,rouge,vert,bleu,SDL_ALPHA_OPAQUE) != 0)
    {
        SDL_Log("Erreur lors du changement de la couleur : %s", SDL_GetError());
    }

    if (SDL_RenderDrawRects(ecran->fond,rects,sudoku.size*sudoku.size+1) != 0)  //gestion des erreurs
    {
        SDL_Log("Erreur lors de la creation des rectangles : %s", SDL_GetError());
    }

    for(short i=0 ; i<sudoku.size ; i++){
        for(short j=0 ; j<sudoku.size ; j++){
            prepTexte(sudoku.sudoku[i][j],sudoku.size,i,j,ecran->fond,ecran->colorT);
        }
    }

    SDL_RenderPresent(ecran->fond);
}
