//
// Created by wolf on 6/10/21.
//

#include <stdio.h>
#include "../modeHandler/modeHandler.h"
#include "../../board/board.h"
#include "../gameLogicHandler/gameLogicHandler.h"
#include "../modeHandler/colors.h"

int get_column_computer_sabotage_victory(struct Player computer) {
    char enemy_token = computer.token == 'X' ? 'O' : 'X';

    //TODO extract !is_cell_empty(row + 1, column) to has_cell_under();

    //TODO extract checks to new functions

    // VERTICAL CHECKS

    // vertical_check : if enemy has 3 in a vertical column
    for (int column = 0; column < BOARD_SIZE; column++) {
        for (int row = BOARD_SIZE - 1; row >= 3; row--) {
            if (board[row][column] == enemy_token &&
                board[row - 1][column] == enemy_token &&
                board[row - 2][column] == enemy_token &&
                can_place_token_here(row - 3, column)) {

//                TODO add to -DEBUG
                printf(RED "SABOTAGING VERTICAL: COLUMN %d\n" RESET, column + 1);
                return column;
            }
        }
    }


    // HORIZONTAL CHECKS


    //   |⬤|⬤|⬤|_|
    // horizontal_right_hole_4_check: If enemy could have 4 in a row and fourth is empty
    for (int row = BOARD_SIZE - 1; row >= 0; row--) {
        for (int column = 0; column < BOARD_SIZE - 3; column++) { //0-4  5 6 7
            if (board[row][column] == enemy_token &&
                board[row][column + 1] == enemy_token &&
                board[row][column + 2] == enemy_token &&
                can_place_token_here(row, column + 3)) {

                printf(CYAN "SABOTAGING HORIZONTAL 4. HOLE: column: %d\n" RESET, column + 4);
                return column + 3;
            }
        }
    }

    //   |⬤|⬤|_|⬤|
    // horizontal_right_hole_check: If enemy could have 4 in a row and fourth is empty
    for (int row = BOARD_SIZE - 1; row >= 0; row--) {
        for (int column = 0; column < BOARD_SIZE - 3; column++) { //0-4  5 6 7
            if (board[row][column] == enemy_token &&
                board[row][column + 1] == enemy_token &&
                can_place_token_here(row, column + 2)&&
                board[row][column + 3] == enemy_token) {

                printf(CYAN "SABOTAGING HORIZONTAL 3. HOLE: column: %d\n" RESET, column + 3);
                return column + 2;
            }
        }
    }

    //   |_|⬤|⬤|⬤|
    // horizontal_left_check: If enemy could have 4 in a row and can  and first is empty
    for (int row = BOARD_SIZE - 1; row >= 0; row--) {
        for (int column = BOARD_SIZE - 1; column >= 3; column--) { // 0 1 2| 3-7
            if (board[row][column] == enemy_token &&
                board[row][column - 1] == enemy_token &&
                board[row][column - 2] == enemy_token &&
                can_place_token_here(row, column - 3)) {

                printf(CYAN "SABOTAGING HORIZONTAL 1. HOLE: column: %d\n" RESET, column - 2);
                return column - 3;
            }
        }
    }

    //   |⬤|_|⬤|⬤|
    // horizontal_left_hole_check: If enemy could have 4 in a row and second is empty
    for (int row = BOARD_SIZE - 1; row >= 0; row--) {
        for (int column = BOARD_SIZE - 1; column >= 3; column--) { //  0 1 2|3-7
            if (board[row][column] == enemy_token &&
                board[row][column - 1] == enemy_token &&
                can_place_token_here(row, column - 2) &&
                board[row][column - 3] == enemy_token) {

                printf(CYAN "SABOTAGING HORIZONTAL 2. HOLE: column: %d\n" RESET, column - 1);
                return column - 2;
            }
        }
    }


    // ASCENDING CHECKS


    //    | | | |⬤|
    //    | | |⬤| |
    //    | |⬤| | |
    //    |X| | | |
    // ascending_diagonal_hole_1_check
    for (int row = BOARD_SIZE - 1; row >= 3; row--) {
        for (int column = 0; column < BOARD_SIZE - 3; column++) {
            if (can_place_token_here(row, column) &&
                board[row - 1][column + 1] == enemy_token &&
                board[row - 2][column + 2] == enemy_token &&
                board[row - 3][column + 3] == enemy_token) {

                printf(YELLOW "SABOTAGING ASC 2. HOLE DIAGN: column: %d\n" RESET, column + 1);
                return column;
            }
        }
    }

    //    | | | |⬤|
    //    | | |⬤| |
    //    | |X| | |
    //    |⬤| | | |
    // ascending_diagonal_hole_2_check: if enemy could have 4 in a row in a diagonal position
    for (int row = BOARD_SIZE - 1; row >= 3; row--) {
        for (int column = 0; column < BOARD_SIZE - 3; column++) {
            if (board[row][column] == enemy_token &&
                is_cell_empty(row - 1, column + 1) && !is_cell_empty(row, column + 1) &&
                board[row - 2][column + 2] == enemy_token &&
                board[row - 3][column + 3] == enemy_token) {

                printf(YELLOW "SABOTAGING ASC 2. HOLE DIAGN: column: %d\n" RESET, column + 2);
                return column + 1;
            }
        }
    }

    //   | | | |⬤|
    //   | | |X| |
    //   | |⬤| | |
    //   |⬤| | | |
    // ascending_diagonal_hole_3_check: if enemy could have 4 in a row in a diagonal position
    for (int row = BOARD_SIZE - 1; row >= 3; row--) {
        for (int column = 0; column < BOARD_SIZE - 3; column++) {
            if (board[row][column] == enemy_token &&
                board[row - 1][column + 1] == enemy_token &&
                    is_cell_empty(row - 2, column + 2) && !is_cell_empty(row - 1, column + 2) &&
                board[row - 3][column + 3] == enemy_token) {

                printf(YELLOW "SABOTAGING ASC 3. HOLE DIAGN: column: %d\n" RESET, column + 3);
                return column + 2;
            }
        }
    }

    //   | | | |X|
    //   | | |⬤| |
    //   | |⬤| | |
    //   |⬤| | | |
    // ascending_diagonal_hole_4_check: if enemy could have 4 in a row in a diagonal position
    for (int row = BOARD_SIZE - 1; row >= 3; row--) {
        for (int column = 0; column < BOARD_SIZE - 3; column++) {
            if (board[row][column] == enemy_token &&
                board[row - 1][column + 1] == enemy_token &&
                board[row - 2][column + 2] == enemy_token &&
                can_place_token_here(row - 3, column + 3)) {

                printf(YELLOW "SABOTAGING ASC 4. HOLE DIAGN: column: %d\n" RESET, column + 4);
                return column + 3;
            }
        }
    }

    // DESCENDING CHECKS -DEBUG->PURPLE

    // |X| | | |
    // | |⬤| | |
    // | | |⬤| |
    // | | | |⬤|
    // descending_diagonal_hole_1_check: if enemy could have 4 in a row in a diagonal position
    for (int row = BOARD_SIZE - 1; row >= 3; row--) {
        for (int column = BOARD_SIZE - 1; column >= 3; column--) {
            if (board[row - 0][column - 0] == enemy_token &&
                board[row - 1][column - 1] == enemy_token &&
                board[row - 2][column - 2] == enemy_token &&
                can_place_token_here(row - 3, column - 3)) {

                printf(PURPLE "SABOTAGING DESC DIAGN HOLE 1: column: %d\n" RESET, column - 2);
                return column - 3;
            }
        }
    }

    // |⬤| | | |
    // | |X| | |
    // | | |⬤| |
    // | | | |⬤|
    // descending_diagonal_hole_2_check: if enemy could have 4 in a row in a diagonal position
    for (int row = BOARD_SIZE - 1; row >= 3; row--) {
        for (int column = BOARD_SIZE - 1; column >= 3; column--) {
            if (board[row - 0][column - 0] == enemy_token &&
                board[row - 1][column - 1] == enemy_token &&
                can_place_token_here(row - 2, column - 2) &&
                board[row - 3][column - 3] == enemy_token) {

                printf(PURPLE "SABOTAGING DESC DIAGN HOLE 2: column: %d\n" RESET, column - 1);
                return column - 2;
            }
        }
    }

    // |⬤| | | |
    // | |⬤| | |
    // | | |X| |
    // | | | |⬤|
    // descending_diagonal_hole_3_check: if enemy could have 4 in a row in a diagonal position
    for (int row = BOARD_SIZE - 1; row >= 3; row--) {
        for (int column = BOARD_SIZE - 1; column >= 3; column--) {
            if (board[row - 1][column - 1] == enemy_token &&
                can_place_token_here(row - 1, column - 1) &&
                board[row - 2][column - 2] == enemy_token &&
                board[row - 3][column - 3] == enemy_token) {

                printf(PURPLE "SABOTAGING DESC DIAGN HOLE 3: column: %d\n" RESET, column);
                return column - 1;
            }
        }
    }

    // |⬤| | | |
    // | |⬤| | |
    // | | |⬤| |
    // | | | |X|
    // descending_diagonal_hole_4_check: if enemy could have 4 in a row in a diagonal position
    for (int row = BOARD_SIZE - 1; row >= 3; row--) {
        for (int column = BOARD_SIZE - 1; column >= 3; column--) {
            if (can_place_token_here(row, column) &&
                board[row - 1][column - 1] == enemy_token &&
                board[row - 2][column - 2] == enemy_token &&
                board[row - 3][column - 3] == enemy_token) {

                printf(PURPLE "SABOTAGING DESC DIAGN HOLE 4: column: %d\n" RESET, column + 1);
                return column;
            }
        }
    }


    
    // OTHER CHECKS -DEBUG->GREEN


    // |_|⬤|⬤|_|
    // horizontal_middle_two_check: if enemy has 2 next to each other  and empty surroundings
    for (int row = BOARD_SIZE - 1; row >= 0; row--) {
        for (int column = 1; column < BOARD_SIZE - 3; column++) {
            if (is_cell_empty(row, column - 1) && !is_cell_empty(row + 1, column - 1) &&
                    board[row][column] == enemy_token &&
                    board[row][column + 1] == enemy_token &&
                is_cell_empty(row, column + 2) && !is_cell_empty(row + 1, column + 2)) {

                printf(GREEN "SABOTAGING SURROUNDINGS: column: %d\n" RESET, column + 3);
                return column + 2;
            }
        }
    }

    return -1;
}

int get_computer_winner_column(struct Player computer) {
    //TODO extract !is_cell_empty(row + 1, column) to has_cell_under();

    //TODO extract checks to new functions

    // VERTICAL CHECKS

    // vertical_check : if enemy has 3 in a vertical column
    for (int column = 0; column < BOARD_SIZE; column++) {
        for (int row = BOARD_SIZE - 1; row >= 3; row--) {
            if (board[row][column] == computer.token &&
                board[row - 1][column] == computer.token &&
                board[row - 2][column] == computer.token &&
                can_place_token_here(row - 3, column)) {

//                TODO add to -DEBUG
                printf(GREEN "WINNING VERTICAL: COLUMN %d\n" RESET, column + 1);
                return column;
            }
        }
    }


    // HORIZONTAL CHECKS


    //   |⬤|⬤|⬤|_|
    // horizontal_right_hole_4_check: If enemy could have 4 in a row and fourth is empty
    for (int row = BOARD_SIZE - 1; row >= 0; row--) {
        for (int column = 0; column < BOARD_SIZE - 3; column++) { //0-4  5 6 7
            if (board[row][column] == computer.token &&
                board[row][column + 1] == computer.token &&
                board[row][column + 2] == computer.token &&
                can_place_token_here(row, column + 3)) {

                printf(GREEN "WINNING HORIZONTAL 4. HOLE: column: %d\n" RESET, column + 4);
                return column + 3;
            }
        }
    }

    //   |⬤|⬤|_|⬤|
    // horizontal_right_hole_check: If enemy could have 4 in a row and fourth is empty
    for (int row = BOARD_SIZE - 1; row >= 0; row--) {
        for (int column = 0; column < BOARD_SIZE - 3; column++) { //0-4  5 6 7
            if (board[row][column] == computer.token &&
                board[row][column + 1] == computer.token &&
                can_place_token_here(row, column + 2)&&
                board[row][column + 3] == computer.token) {

                printf(GREEN "WINNING HORIZONTAL 3. HOLE: column: %d\n" RESET, column + 3);
                return column + 2;
            }
        }
    }

    //   |_|⬤|⬤|⬤|
    // horizontal_left_check: If enemy could have 4 in a row and can  and first is empty
    for (int row = BOARD_SIZE - 1; row >= 0; row--) {
        for (int column = BOARD_SIZE - 1; column >= 3; column--) { // 0 1 2| 3-7
            if (board[row][column] == computer.token &&
                board[row][column - 1] == computer.token &&
                board[row][column - 2] == computer.token &&
                can_place_token_here(row, column - 3)) {

                printf(GREEN "WINNING HORIZONTAL 1. HOLE: column: %d\n" RESET, column - 2);
                return column - 3;
            }
        }
    }

    //   |⬤|_|⬤|⬤|
    // horizontal_left_hole_check: If enemy could have 4 in a row and second is empty
    for (int row = BOARD_SIZE - 1; row >= 0; row--) {
        for (int column = BOARD_SIZE - 1; column >= 3; column--) { //  0 1 2|3-7
            if (board[row][column] == computer.token &&
                board[row][column - 1] == computer.token &&
                can_place_token_here(row, column - 2) &&
                board[row][column - 3] == computer.token) {

                printf(GREEN "WINNING HORIZONTAL 2. HOLE: column: %d\n" RESET, column - 1);
                return column - 2;
            }
        }
    }


    // ASCENDING CHECKS


    //    | | | |⬤|
    //    | | |⬤| |
    //    | |⬤| | |
    //    |X| | | |
    // ascending_diagonal_hole_1_check
    for (int row = BOARD_SIZE - 1; row >= 3; row--) {
        for (int column = 0; column < BOARD_SIZE - 3; column++) {
            if (can_place_token_here(row, column) &&
                board[row - 1][column + 1] == computer.token &&
                board[row - 2][column + 2] == computer.token &&
                board[row - 3][column + 3] == computer.token) {

                printf(GREEN "WINNING ASC 2. HOLE DIAGN: column: %d\n" RESET, column + 1);
                return column;
            }
        }
    }

    //    | | | |⬤|
    //    | | |⬤| |
    //    | |X| | |
    //    |⬤| | | |
    // ascending_diagonal_hole_2_check: if enemy could have 4 in a row in a diagonal position
    for (int row = BOARD_SIZE - 1; row >= 3; row--) {
        for (int column = 0; column < BOARD_SIZE - 3; column++) {
            if (board[row][column] == computer.token &&
                is_cell_empty(row - 1, column + 1) && !is_cell_empty(row, column + 1) &&
                board[row - 2][column + 2] == computer.token &&
                board[row - 3][column + 3] == computer.token) {

                printf(GREEN "WINNING ASC 2. HOLE DIAGN: column: %d\n" RESET, column + 2);
                return column + 1;
            }
        }
    }

    //   | | | |⬤|
    //   | | |X| |
    //   | |⬤| | |
    //   |⬤| | | |
    // ascending_diagonal_hole_3_check: if enemy could have 4 in a row in a diagonal position
    for (int row = BOARD_SIZE - 1; row >= 3; row--) {
        for (int column = 0; column < BOARD_SIZE - 3; column++) {
            if (board[row][column] == computer.token &&
                board[row - 1][column + 1] == computer.token &&
                is_cell_empty(row - 2, column + 2) && !is_cell_empty(row - 1, column + 2) &&
                board[row - 3][column + 3] == computer.token) {

                printf(GREEN "WINNING ASC 3. HOLE DIAGN: column: %d\n" RESET, column + 3);
                return column + 2;
            }
        }
    }

    //   | | | |X|
    //   | | |⬤| |
    //   | |⬤| | |
    //   |⬤| | | |
    // ascending_diagonal_hole_4_check: if enemy could have 4 in a row in a diagonal position
    for (int row = BOARD_SIZE - 1; row >= 3; row--) {
        for (int column = 0; column < BOARD_SIZE - 3; column++) {
            if (board[row][column] == computer.token &&
                board[row - 1][column + 1] == computer.token &&
                board[row - 2][column + 2] == computer.token &&
                can_place_token_here(row - 3, column + 3)) {

                printf(GREEN "WINNING ASC 4. HOLE DIAGN: column: %d\n" RESET, column + 4);
                return column + 3;
            }
        }
    }

    // DESCENDING CHECKS -DEBUG->PURPLE

    // |X| | | |
    // | |⬤| | |
    // | | |⬤| |
    // | | | |⬤|
    // descending_diagonal_hole_1_check: if enemy could have 4 in a row in a diagonal position
    for (int row = BOARD_SIZE - 1; row >= 3; row--) {
        for (int column = BOARD_SIZE - 1; column >= 3; column--) {
            if (board[row - 0][column - 0] == computer.token &&
                board[row - 1][column - 1] == computer.token &&
                board[row - 2][column - 2] == computer.token &&
                can_place_token_here(row - 3, column - 3)) {

                printf(GREEN "WINNING DESC DIAGN HOLE 1: column: %d\n" RESET, column - 2);
                return column - 3;
            }
        }
    }

    // |⬤| | | |
    // | |X| | |
    // | | |⬤| |
    // | | | |⬤|
    // descending_diagonal_hole_2_check: if enemy could have 4 in a row in a diagonal position
    for (int row = BOARD_SIZE - 1; row >= 3; row--) {
        for (int column = BOARD_SIZE - 1; column >= 3; column--) {
            if (board[row - 0][column - 0] == computer.token &&
                board[row - 1][column - 1] == computer.token &&
                can_place_token_here(row - 2, column - 2) &&
                board[row - 3][column - 3] == computer.token) {

                printf(GREEN "WINNING DESC DIAGN HOLE 2: column: %d\n" RESET, column - 1);
                return column - 2;
            }
        }
    }

    // |⬤| | | |
    // | |⬤| | |
    // | | |X| |
    // | | | |⬤|
    // descending_diagonal_hole_3_check: if enemy could have 4 in a row in a diagonal position
    for (int row = BOARD_SIZE - 1; row >= 3; row--) {
        for (int column = BOARD_SIZE - 1; column >= 3; column--) {
            if (board[row - 1][column - 1] == computer.token &&
                can_place_token_here(row - 1, column - 1) &&
                board[row - 2][column - 2] == computer.token &&
                board[row - 3][column - 3] == computer.token) {

                printf(GREEN "WINNING DESC DIAGN HOLE 3: column: %d\n" RESET, column);
                return column - 1;
            }
        }
    }

    // |⬤| | | |
    // | |⬤| | |
    // | | |⬤| |
    // | | | |X|
    // descending_diagonal_hole_4_check: if enemy could have 4 in a row in a diagonal position
    for (int row = BOARD_SIZE - 1; row >= 3; row--) {
        for (int column = BOARD_SIZE - 1; column >= 3; column--) {
            if (can_place_token_here(row, column) &&
                board[row - 1][column - 1] == computer.token &&
                board[row - 2][column - 2] == computer.token &&
                board[row - 3][column - 3] == computer.token) {

                printf(GREEN "WINNING DESC DIAGN HOLE 4: column: %d\n" RESET, column + 1);
                return column;
            }
        }
    }



    // OTHER CHECKS -DEBUG->GREEN


    // |_|⬤|⬤|_|
    // horizontal_middle_two_check: if enemy has 2 next to each other  and empty surroundings
    for (int row = BOARD_SIZE - 1; row >= 0; row--) {
        for (int column = 1; column < BOARD_SIZE - 3; column++) {
            if (is_cell_empty(row, column - 1) && !is_cell_empty(row + 1, column - 1) &&
                board[row][column] == computer.token &&
                board[row][column + 1] == computer.token &&
                is_cell_empty(row, column + 2) && !is_cell_empty(row + 1, column + 2)) {

                printf(GREEN "WINNING SURROUNDINGS: column: %d\n" RESET, column + 3);
                return column + 2;
            }
        }
    }

    return -1;
}