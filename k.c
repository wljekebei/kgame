#include <stdio.h>
#include <stdlib.h>
#include "k.h"
#include <time.h>
#include <string.h>

void add_random_tile(struct game *game){
    srand(time(NULL));
    int row, col;
    // find random, but empty tile
    do{
        row = rand() % SIZE;
        col = rand() % SIZE;
    }while(game->board[row][col] != ' ');

    // place to the random position 'A' or 'B' tile
    if(rand() % 2 == 0){
        game->board[row][col] = 'A';
    }else{
        game->board[row][col] = 'B';
    }
}

bool is_game_won(const struct game game) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (game.board[i][j] == 'K')
            return true;
        }
    }
    return false;
}

bool is_move_possible(const struct game game) {
    for (int i = 0; i < SIZE - 1; i++) {
        for (int j = 0; j < SIZE - 1; j++) {
            if (game.board[i][j] == game.board[i+1][j]) {
                return 1;
            } else if (game.board[i][j] == game.board[i][j+1]) {
                return 1;
            } else if (game.board[i][j] == ' ') {
                return 1;
            } else if (game.board[i+1][j] == ' ') {
                return 1;
            } else if (game.board[i][j+1] == ' ') {
                return 1;
            } else if (game.board[i+1][j+1] == ' ') {
                return 1;
            }
        }
    }   
    return 0;
}

bool update(struct game *game, int dir) {
    char pism[] = "ABCDEFGHIJK";
    int hodn[] = {2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048};

    if (dir != 8 && dir != 4 && dir != 6 && dir != 5) {
        printf("Error: incorrect input\n");
        return false;
    } else if (dir == 6) { // right
        for (int i = 0; i < SIZE; i++) {
            int comb = 0;
            for (int j = SIZE - 1; j >= 0; j--) {
                int jj = SIZE - comb - 1;
                while (jj > 0) {
                    if (game->board[i][jj] == ' ') { // if space
                        if (game->board[i][jj-1] != ' ') {
                            game->board[i][jj] = game->board[i][jj-1];
                            game->board[i][jj-1] = ' ';
                            jj--;
                        } else {
                            jj--;
                        }
                    } else if (game->board[i][jj] == game->board[i][jj-1]) { // if similar
                        game->board[i][jj] = (int)game->board[i][jj] + 1;
                        for (int n = 0; n < 11; n++) {
                            if (game->board[i][jj] == pism[n]) {
                                game->score += hodn[n];
                            }
                        }                        
                        game->board[i][jj-1] = ' ';
                        jj--;
                        comb++;
                    } else { // if different
                        jj--;
                    }
                }
            }
        }
    } else if (dir == 4) { // left
        for (int i = 0; i < SIZE; i++) {
            int comb = 0;
            for (int j = 0; j < SIZE - 1; j++) {
                int jj = comb;
                while (jj < SIZE - 1) {
                    if (game->board[i][jj] == ' ') { // if space
                        if (game->board[i][jj+1] != ' ') {
                            game->board[i][jj] = game->board[i][jj+1];
                            game->board[i][jj+1] = ' ';
                            jj++;
                        } else {
                            jj++;
                        }
                    } else if (game->board[i][jj] == game->board[i][jj+1]) { // if similar
                        game->board[i][jj] = (int)game->board[i][jj] + 1;
                        for (int n = 0; n < 11; n++) {
                            if (game->board[i][jj] == pism[n]) {
                                game->score += hodn[n];
                            }
                        }                        
                        game->board[i][jj+1] = ' ';
                        jj++;
                        comb++;
                    } else { // if different
                        jj++;
                    }
                }
            }
        }
    } else if (dir == 8) { // up
        for (int j = 0; j < SIZE; j++) {
            int comb = 0;
            for (int i = 0; i < SIZE - 1; i++) {
                int ii = comb;
                while (ii < SIZE - 1) {
                    if (game->board[ii][j] == ' ') { // if space
                        if (game->board[ii+1][j] != ' ') {
                            game->board[ii][j] = game->board[ii+1][j];
                            game->board[ii+1][j] = ' ';
                            ii++;
                        } else {
                            ii++;
                        }
                    } else if (game->board[ii][j] == game->board[ii+1][j]) { // if similar
                        game->board[ii][j] = (int)game->board[ii][j] + 1;
                        for (int n = 0; n < 11; n++) {
                            if (game->board[ii][j] == pism[n]) {
                                game->score += hodn[n];
                            }
                        }                        
                        game->board[ii+1][j] = ' ';
                        ii++;
                        comb++;
                    } else { // if different
                        ii++;
                    }
                }
            }
        }
    } else if (dir == 5) { // down
        for (int j = 0; j < SIZE; j++) {
            int comb = 0;
            for (int i = SIZE-1; i >= 0; i--) {
                int ii = SIZE - comb - 1;
                while (ii > 0) {
                    if (game->board[ii][j] == ' ') { // if space
                        if (game->board[ii-1][j] != ' ') {
                            game->board[ii][j] = game->board[ii-1][j];
                            game->board[ii-1][j] = ' ';
                            ii--;
                        } else {
                            ii--;
                        }
                    } else if (game->board[ii][j] == game->board[ii-1][j]) { // if similar
                        game->board[ii][j] = (int)game->board[ii][j] + 1;
                        for (int n = 0; n < 11; n++) {
                            if (game->board[ii][j] == pism[n]) {
                                game->score += hodn[n];
                            }
                        }
                        game->board[ii-1][j] = ' ';
                        ii--;
                        comb++;
                    } else { // if different
                        ii--;
                    }
                }
            }
        }
    } else {
        return false;
    }

    return true;
}