#include <process.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>

void clear_console();
void display_board(Board *board);
void display_start_menu();
void display_choice_mode_game();
void display_choice_map();
void display_choice_server();



void display_start_menu(){
    int cursorY =1;
    //int exit = 0;
    system("cls");
    printf("\n===============> Bienvenue dans Casse Briques <===============\n\n\n\n\n\n\n\n\t");
    system("psause");
    clear_console();

    while(1){
        clear_console();

        printf("______________________________\n\n");
        printf("\tMENU PRINCIPAL");
        printf("\n______________________________\n\n\n");
        if( cursorY == 1){
            printf("[X] Jouer\n\n[ ] Configuration\n\n[ ] Quitter");
        }
        else if(cursorY == 2) {
            printf("[ ] Jouer\n\n[X] Configuration\n\n[ ] Quitter");
        }else {
            printf("[ ] Jouer\n\n[ ] Configuration\n\n[X] Quitter");
        }

        printf("\n");
        switch (_getch()) {
            case 122:
                cursorY--;
                if(cursorY == 0 ) cursorY =1;
                break;
            case 115:
                cursorY ++;
                if(cursorY == 4 ) cursorY =3;
                break;
            case 13 :
                if(cursorY == 3){
                    return;

                }else if(cursorY == 2){
                    //fichier de configuration
                }
                else {
                    display_choice_mode_game();
                }
                break;
            }

        }



}


void display_choice_mode_game(){
    system("cls");
    int cursorY = 1;
    while(1){
        system("cls");
        printf("___________________________\n\n");
        printf("\tMODE DE JEU");
        printf("\n___________________________\n\n\n");
        if(cursorY == 1){
            printf("[X] Jouer contre l'ordinateur\n\n[ ] Jouer en Local\n\n[ ] Jouer en ligne\n\n[ ] Retour");
        } else if(cursorY == 2){
            printf("[ ] Jouer contre l'ordinateur\n\n[X] Jouer en Local\n\n[ ] Jouer en ligne\n\n[ ] Retour");
        }else if(cursorY == 3){
            printf("[ ] Jouer contre l'ordinateur\n\n[ ] Jouer en Local\n\n[X] Jouer en ligne\n\n[ ] Retour");
        }else {
            printf("[ ] Jouer contre l'ordinateur\n\n[ ] Jouer en Local\n\n[ ] Jouer en ligne\n\n[X] Retour");
        }

        switch (_getch()) {
            case 122:
                cursorY--;
                if(cursorY == 0 ) cursorY =1;
                break;
            case 115:
                cursorY ++;
                if(cursorY == 5 ) cursorY =4;
                break;

            case 13 :
                if(cursorY == 4){
                    return;
                } else if(cursorY == 1 || cursorY == 2) {
                    display_choice_map();
                } else if(cursorY == 3){
                    display_choice_server();
                }
                break;
        }

    }

}


void display_choice_map() {

    int cursorY = 1;
    while (1) {
        system("cls");
        printf("_____________________\n\n");
        printf("\tCARTES");
        printf("\n_____________________\n\n\n");
        if (cursorY == 1) {
            printf("[X] \n\n[ ] \n\n[ ] \n\n[ ] Retour");
        } else if (cursorY == 2) {
            printf("[ ] \n\n[X] \n\n[ ] \n\n[ ] Retour");
        } else if (cursorY == 3) {
            printf("[ ] \n\n[ ] \n\n[X] \n\n[ ] Retour");
        } else {
            printf("[ ] \n\n[ ]\n\n[ ] \n\n[X] Retour");
        }
        switch (_getch()) {
            case 122:
                cursorY--;
                if (cursorY == 0) cursorY = 1;
                break;
            case 115:
                cursorY++;
                if (cursorY == 5) cursorY = 4;
                break;

            case 13 :
                if (cursorY == 4) {
                    return;
                    //Fonction nbre de joueur
                    //break;
                }

        }


    }

}

void display_choice_server(){

    int cursorY = 1;
    while (1) {
        system("cls");
        printf("________________________\n\n");
        printf("\tEN LIGNE");
        printf("\n________________________\n\n\n");
        if (cursorY == 1) {
            printf("[X] D%cmarrer un serveur \n\n[ ] Rejoindre un serveur \n\n[ ] Retour",130);
        } else if (cursorY == 2) {
            printf("[ ] D%cmarrer un serveur \n\n[X] Rejoindre un serveur \n\n[ ] Retour",130);
        } else {
            printf("[ ] D%cmarrer un serveur \n\n[ ] Rejoindre un serveur \n\n[X] Retour",130);
        }

        switch (_getch()) {
            case 122:
                cursorY--;
                if (cursorY == 0) cursorY = 1;
                break;
            case 115:
                cursorY++;
                if (cursorY == 4) cursorY = 3;
                break;

            case 13 :
                if (cursorY == 3) {
                    return;
                    //Fonction nbre de joueur
                    //break;
                }
        }

    }

}


void display_board(Board *board){
    clear_console();
    //header
    unsigned short selected_map = board->selected_map;
    for (int i = 0; i < board->map[selected_map]->rows; ++i) {
        for (int j = 0; j <= board->map[selected_map]->columns; ++j) {
            printf("%c", board->map[selected_map]->body[i][j]);
        }
        printf("\n");
    }
    //footer
}

void clear_console() {
    system("cls");
}