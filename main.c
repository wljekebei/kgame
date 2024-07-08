#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#include "k.h"
#include <string.h>
#include "hof.h"

int main() {
    struct game game = {
        .board = {
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        .score = 0
    };

    add_random_tile(&game);  
    add_random_tile(&game);

    printf("\nTry to reach the 'K' letter. Enter any letter to quit\n\n");

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf(" %c |", game.board[i][j]);
        }
        printf("\n");
    }

    int dir = 0;
    int counter = 1;

    while (is_game_won(game) == false) {
        if (!is_move_possible(game)) {
            break;
        }
        printf("\nMove %d | Score: %d | Direction: ", counter, game.score);
        int res = scanf("%d", &dir);
        if (res == 0) {
            break;
        }
        if (update(&game, dir) == 0) {
            continue;
        } else {
            int space = 0;
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    if (game.board[i][j] == DELIMITER) {
                        space++;
                        break;
                    }
                }
            }
            if (space != 0) {
                add_random_tile(&game);
            } else {
                printf("Error: choose another direction\n");
                continue;
            }
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    printf(" %c |", game.board[i][j]);
                }
                printf("\n");
            }
            counter++;
        }
    }

    while ( getchar() != '\n' );

    if (is_game_won(game) == true) {
        printf("\nCongratulations! You won!\n");
    } else {
        printf("\nGame over\n");
    }

    struct player list[10];
    int size = load(list);
    printf("\nEnter your name: ");
    struct player player = {
        .score = game.score
    };
    fgets(player.name, 30, stdin);
    player.name[strlen(player.name)-1] = '\0';
    add_player(list, &size, player);
    return 0;
}