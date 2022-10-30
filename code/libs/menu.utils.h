
void menu_home_case(Board *board) {
    menus_index next_menu[] = {menu_game_mode, menu_options, menu_patch_notes, menu_credits, menu_leave};
    choices_index choices_menu[] = {choice_play, choice_options, choice_patch_notes, choice_credits, choice_leave};

    board->menus[board->current_menu]->nb_choice = 5;
    board->menus[board->current_menu]->prev_menu = menu_leave;
    board->menus[board->current_menu]->next_menu = next_menu[board->current_choice];

    display_menu(board, choices_menu);
}

void menu_options_case(Board *board) {
    menus_index next_menu[] = {menu_languages};
    choices_index choices_menu[] = {choice_languages, choice_back};

    board->menus[board->current_menu]->nb_choice = 2;
    board->menus[board->current_menu]->prev_menu = menu_home;
    board->menus[board->current_menu]->next_menu = next_menu[board->current_choice];

    display_menu(board, choices_menu);
}

void menu_game_mode_case(Board *board) {
    menus_index next_menu[] = {menu_home, menu_leave, menu_home, menu_leave};
    choices_index choices_menu[] = {choice_solo, choice_local, choice_online, choice_back};

    board->menus[board->current_menu]->nb_choice = 4;
    board->menus[board->current_menu]->prev_menu = menu_home;
    board->menus[board->current_menu]->next_menu = next_menu[board->current_choice];

    display_menu(board, choices_menu);
}

void menu_patch_notes_case(Board *board) {
    if(!file_display_content(str_cat(PATCH_NOTES_DIR, board->config->language))) {
        board->current_menu = menu_home;
    } else {
        board->menus[board->current_menu]->prev_menu = menu_home;
    }
}

void menu_credits_case(Board *board) {
    if(!file_display_content(str_cat(CREDITS_DIR, board->config->language))) {
        board->current_menu = menu_home;
    } else {
        board->menus[board->current_menu]->prev_menu = menu_home;
    }
}