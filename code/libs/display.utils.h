#include <process.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdarg.h>

void clear_console();
void display_board(Board *board);
void display_start_menu();
void display_choice_mode_game();
void display_choice_map();
void display_choice_server();

void display_header();

int display(int *cursor, int *selected_menu);

void display_header() {
    clear_console();
    printf("\n===============> Bienvenue dans Casse Briques <===============\n\n\n\n\n\n\n\n\t");
    system("pause");
}

int display(int *cursor, int *selected_menu) {

    if(*selected_menu == 1){
        *cursor = (*cursor == 4) ? 3 : *cursor;
        display_start_menu(*cursor);
    }else if(*selected_menu == 2){
        *cursor = (*cursor == 5) ? 4 : *cursor;
        display_choice_mode_game(*cursor);
    } else if(*selected_menu==3){
        *cursor = (*cursor == 5) ? 4 : *cursor;
        display_choice_map(*cursor);
    } else if(*selected_menu == 4){
        *cursor = (*cursor == 4) ? 3 : *cursor;
        display_choice_server(*cursor);
    }
    int event = getch();
    switch (event) {
        case 72:
            *cursor-=1;
            *cursor = (*cursor == 0) ? 1 : *cursor;
            break;
        case 80:
            *cursor+=1;
            break;
        case 13:
            if(*selected_menu == 1 && *cursor == 3){
                return 0;
            } else if((*selected_menu == 2 && *cursor == 4) || (*selected_menu==3 && *cursor == 4)){
                *selected_menu -= 1;
            }else if(*selected_menu == 4 && *cursor == 3 ){
                *selected_menu = 2;
            }
            else if(*selected_menu == 2 && *cursor == 3){
                *selected_menu = 4;
            }
            else {
                *selected_menu += 1;
            }
            break;
        default:
            break;
    }
    return 1;
}

/**
 * @function : Affiche le menu principal
 * @features : 1.Jouer
 *             2. Changer fichier de configuration
 *             3. Quitter
 */
void display_start_menu(int cursor) {
    clear_console();
    printf("______________________________\n\n");
    printf("\tMENU PRINCIPAL");
    printf("\n______________________________\n\n\n");
    printf("[%c] %s \n\n[%c] %s \n\n[%c] %s", cursor == 1 ? 'X' : ' ', "Jouer", cursor == 2 ? 'X' : ' ',
           "Configuration", cursor == 3 ? 'X' : ' ', "Quitter");
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
void display_choice_map(int cursor) {
    system("cls");
    printf("_____________________\n\n");
    printf("\tCARTES");
    printf("\n_____________________\n\n\n");
    printf("[%c] %s \n\n[%c] %s \n\n[%c] %s \n\n[%c] %s", cursor == 1 ? 'X' : ' ', "", cursor == 2 ? 'X' : ' ',
     "", cursor == 3 ? 'X' : ' ', "", cursor == 4 ? 'X' : ' ', "Retour");

}

/**
 * @function : Affiche le mode en ligne
 * @features : 1. Démarrer un serveur
 *             2. Rejoindre un serveur
 */
void display_choice_server(int cursor) {
        system("cls");
        printf("________________________\n\n");
        printf("\tEN LIGNE");
        printf("\n________________________\n\n\n");
        printf("[%c] %s \n\n[%c] %s \n\n[%c] %s ", cursor == 1 ? 'X' : ' ', "Creer un serveur",
               cursor == 2 ? 'X' : ' ', "Demarrer un serveur", cursor == 3 ? 'X' : ' ', "Retour");

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