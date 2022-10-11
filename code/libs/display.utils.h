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


/**
 * @function : Affiche le menu principal
 * @features : 1.Jouer
 *             2. Changer fichier de configuration
 *             3. Quitter
 */
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
        printf("[%c] %s \n\n[%c] %s \n\n[%c] %s", cursorY == 1 ? 'X' : ' ',"Jouer",cursorY == 2 ? 'X' : ' ', "Configuration", cursorY == 3 ? 'X' : ' ', "Quitter");

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

/**
 * @function : Affiche les different mode de jeu
 * @features : 1.Jouer contre l'ordinateur
 *             2. Jouer en Local
 *             3. Jouer en Ligne
 *             4.Retour
 */
void display_choice_mode_game(){
    system("cls");
    int cursorY = 1;
    while(1){
        system("cls");
        printf("___________________________\n\n");
        printf("\tMODE DE JEU");
        printf("\n___________________________\n\n\n");
        printf("[%c] %s \n\n[%c] %s \n\n[%c] %s \n\n[%c] %s", cursorY == 1 ? 'X' : ' ',"Jouer contre l'ordinateur",cursorY == 2 ? 'X' : ' ', "Jouer en local", cursorY == 3 ? 'X' : ' ', "Jouer en Ligne", cursorY == 4 ? 'X' : ' ', "Retour");

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

/**
 * @function : Affiche les cartes
 */
void display_choice_map() {

    int cursorY = 1;
    while (1) {
        system("cls");
        printf("_____________________\n\n");
        printf("\tCARTES");
        printf("\n_____________________\n\n\n");
        printf("[%c] %s \n\n[%c] %s \n\n[%c] %s \n\n[%c] %s", cursorY == 1 ? 'X' : ' ',"",cursorY == 2 ? 'X' : ' ', "", cursorY == 3 ? 'X' : ' ', "", cursorY == 4 ? 'X' : ' ', "Retour");

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

/**
 * @function : Affiche le mode en ligne
 * @features : 1. Démarrer un serveur
 *             2. Rejoindre un serveur
 */
void display_choice_server(){

    int cursorY = 1;
    while (1) {
        system("cls");
        printf("________________________\n\n");
        printf("\tEN LIGNE");
        printf("\n________________________\n\n\n");
        printf("[%c] %s \n\n[%c] %s \n\n[%c] %s ", cursorY == 1 ? 'X' : ' ',"Creer un serveur",cursorY == 2 ? 'X' : ' ', "Demarrer un serveur", cursorY == 3 ? 'X' : ' ', "Retour");


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