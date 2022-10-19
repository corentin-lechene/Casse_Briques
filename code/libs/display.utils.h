#include <process.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdarg.h>

void clear_console();

void display_board(Board *board);

void display_choice_map(int cursor);

void display_choice_server(int cursor);

void display_header();

int display(int *selected_choice, int *selected_menu, int *has_move);

void display_menu(int *cursor, ...);



void display_header() {
    clear_console();
    printf("\n===============> Bienvenue dans Casse Briques <===============\n\n\n\n\n\n\n\n\t");
    system("pause");
}


int display(int *selected_choice, int *selected_menu, int *has_move) {
    //Controler les rafraichissements
    if(*has_move == 1){
        switch (*selected_menu) {
            case 0 :
                return 0;
            case 1 :
                display_menu(selected_choice,"MENU PRINCIPAL","Jouer","Configuration","Quitter", NULL);
                break;
            case 2 :
                display_menu(selected_choice,"MODE DE JEU","Jouer contre l'ordinateur","Jouer en Local","Jouer en Ligne","Retour", NULL);
                break;
            case 3 :
                display_menu(selected_choice, "CARTES"," "," "," ","Retour", NULL);
                break;
            case 4 :
                display_menu(selected_choice, "EN LIGNE","Demarrer un serveur","Rejoindre un serveur","Retour", NULL);
                break;

            default:
                break;
        }
    }
    int event = getch();
    switch (event) {
        case 72:
            if(*selected_choice - 1 >= 0 ){
                *has_move = 1;
                *selected_choice-=1;
            }else {
                *has_move = 0;
            }
            break;
        case 80:
            *selected_choice+=1;
            *has_move = 1;
            break;
        case 13:
            if(*selected_menu == 1 && *selected_choice == 2){
                return 0;
            }else if((*selected_menu == 2 && *selected_choice == 3) || (*selected_menu == 3 && *selected_choice == 3)){
                *selected_menu -= 1;
            }else if(*selected_menu == 4 && *selected_choice == 2 ){
                *selected_menu = 2;
            }
            else if(*selected_menu == 2 && *selected_choice == 2){
                *selected_menu = 4;
            }
            else {
                if(*selected_menu + 1 < 5 ){
                    *selected_menu += 1;
                }
            }
            break;
        default:
            break;
    }

    return 1;
}

void display_menu(int *cursor, ...) {
    clear_console();
    va_list ap, temp;
    va_start(ap, cursor);
    temp = ap;
    int i = 0;
    while (va_arg(ap, char* ) != NULL) {
        i++;
    }
    va_end(ap);
    if(*cursor >= i-1) {
        *cursor = i-2;
    }

    va_start(temp, cursor);
    char *arg = va_arg(temp, char* );
    printf("----------------------------------\n\n");
    printf("\t%s\n", arg);
    printf("\n----------------------------------\n\n");
    arg = va_arg(temp, char*);
    for (int j = 0; j < i-1; ++j) {
        printf("[%c] %s\n\n", j == *cursor ? 'X' : ' ', arg);
        arg = va_arg(temp, char*);
    }
    va_end(temp);

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


void display_board(Board *board) {
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