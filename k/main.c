//
//  main.c
//  k-my
//  TEST VERSION 2.0
//
//  Created by Martin M. on 7.4.2015.
//  Last Edit by Martin M. on 18.4.2015.
//  Copyright (c) 2015 Martin M. All rights reserved.
//  xCode 7.x
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "hof.h"
#include "k.h"

#define matrix 4;

int main(int argc, const char * argv[]) {
    srand ((unsigned int)time(NULL));

    printf("Welcome to K game or \"2048\" game!\n");
    printf("Control key: \n\tUP:\tW (w)\n\tDOWN:\tS (s)\n\tLEFT:\tA (a)\n\tRIGHT:\tD (d)\n\n");


    // PLAYER NAME
    PLAYER Player;
    printf("Hi, your name?: ");
    scanf("%29s", Player.name);

    if (strlen(Player.name) > 29) {
        Player.name[29] = '\0';
        printf("Yours new name is: %s\n", Player.name);
    }
    printf("\n");

    int matrixInt = matrix;

    int dx, dy = 0;
    char keys[2];

    // DEFAULT GAME
    GAME Game = {
        .board = {
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        .score = 0
    };

    // DEFAULT RANDOM
    for (int i = 0; i < 2; i++) add_random_tile(&Game);
    bool badKey = false;
    do {
        printf("Score: %d\n", Game.score);
        printf("Actual Render: \n");

        render(Game); // RENDER GAME

        printf("\nType in the direction (WASD): ");
        scanf("%1s", keys);
        keys[0] |= 0x20; // TO LOWER

        printf("\t");
        dx = dy = 0;
        switch (keys[0]) {
            case 'w':
                printf("TYPE UP!");
                dy = -1;
                break;
            case 's':
                printf("TYPE DOWN!");
                dy = 1;
                break;
            case 'a':
                printf("TYPE LEFT!");
                dx = -1;
                break;
            case 'd':
                printf("TYPE RIGHT!");
                dx = 1;
                break;

            default: printf("Ups, bad key!"); badKey = true; break;
        }

        if (badKey) break;

        // UPDATE GAME
        if (!update(&Game, dy, dx)) printf("\n\nUps, no update!");

        printf("\n\n");

        // IS GAME WON?
        if (is_game_won(Game)) {
            printf("Congratulations, you won!\n");
            break;
        }

        // NEXT RANDOM
        for (int i = 0; i < matrixInt; i++) {
            if (searchLetter(Game.board[i], " ", &matrixInt)) {
                add_random_tile(&Game);
                break;
            }
        }

        // IS MOVE?
        if (!is_move_possible(Game)) {
            printf("-------------------------------------------------\n\nLast Render: \n");
            render(Game); // RENDER GAME
            printf("\nUps, GAME OVER with %d score!", Game.score);
            break;
        }

    } while( true );

    // ADD PLAYER
    PLAYER list[10];
    Player.score = Game.score;

    int size = load(list);
    bool result = add_player(list, &size, Player);

    printf("\n");
    if (result) {
        size = load(list);
        printf("Added you the score list with %d bounds and your place on the list is %d.!\n", Game.score, placeInList(Player, list, size));
    } else
        printf("Dont added you the score list.\n");

    return 0;
}
