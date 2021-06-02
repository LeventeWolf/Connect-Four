#include <stdio.h>
#include <stdbool.h>
#include "gameMaster.h"
#include "../handlers/modeHandler/modeHandler.h"
#include "../handlers/inputHandler/inputHandler.h"
#include "../board/board.h"

void start() {
    init();

    show_title();
    main_menu();
}

void init() {
    init_modes();
    init_board();
}

void show_title() {
    printf(TITLE_PADDING "Connect Four" TITLE_PADDING "\n");
}

void main_menu() {
    printf(PADDING "--Main Menu--" PADDING "\n");
    while(true){
        show_modes();
        if (play_mode(get_main_menu_choice()) == 0) {
            break;
        }
    }
}
