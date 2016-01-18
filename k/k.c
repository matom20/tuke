#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "k.h"

#define MATRIX 4

// MAGIC FUNCTION from k.h
void add_random_tile(GAME *game){
    int row, col;
    // find random, but empty tile
    do {
        row = rand() % 4;
        col = rand() % 4;
    } while(game->board[row][col] != ' ');

    // place to the random position 'A' or 'B' tile
    int tile = 'A' + (rand() % 2);
    game->board[row][col] = tile;
}

/**
 * Function finding charakters in string
 * @param text list of characters
 * @param find character finding in list
 * @param size array
 * @return status search true or false
 */
bool searchLetter(const char text[], const char *find, const int *size){
    int count = 0;
    for (int i = 0; i < *size; i++) {
        if (text[i] == *find) {
            count++;
            break;
        }
    }
    if (count != 0) return true; else return false;
}

// MAGIC FUNCTION from k.h
void render(const GAME game) {
    int matrixInt = MATRIX;

    printf("\t+---+---+---+---+");
    // | A |   |   |   |
    for (int i = 0; i < matrixInt; i++) {
        printf("\n\t| ");
        for (int s = 0; s < matrixInt; s++) {
            printf("%c", game.board[i][s]);
            printf(" | ");
        }
        printf("\n");
        printf("\t+---+---+---+---+");
    }
}

// MAGIC FUNCTION from k.h
bool is_game_won(const GAME game) {
    int matrixInt = MATRIX;
    for (int i = 0; i < matrixInt; i++)
        if (searchLetter(game.board[i], "K", &matrixInt)) return true;
    return false;
}

// MAGIC FUNCTION from k.h
bool is_move_possible(const GAME game) {
    int matrixInt = MATRIX;

    if (is_game_won(game)) return false;

    for (int i = 0; i < matrixInt; i++) {
        if (searchLetter(game.board[i], " ", &matrixInt)) return true;
        // LETTER
        for (int s = 0; s < matrixInt; s++) {

            if ( (matrixInt-1 > s && (char)game.board[i][s] == (char)game.board[i][s+1]) || // CHECK RIGHT
                (matrixInt-1 > i && (char)game.board[i][s] == (char)game.board[i+1][s]) // CHECK DOWN
                ) return true;
        }
    }
    return false;
}

/**
 * Function updating score for player
 * @param game reference to the game object
 * @param letter for math score
 */
void update_score(GAME *game, const char letter) {
    game->score += pow(2, (int)((int)letter - 'A' + 1));
}

/**
 * Function replace letter A A -> B
 * @param game reference to the game object
 * @param i is column of matrix
 * @param dy movement in y-axe
 * @param dx movement in x-axe
 */

bool replace_matrix(GAME *game, int i, int *dy, int *dx) {
    int m, g, swapArray[10], d; bool retrn = false;
    int matrixInt = MATRIX;

    // CHECK FOR LOOP
    m = g = 0;
    for (int s = 0; s < matrixInt; s++) {

        if (*dy != 0) { swapArray[0] = s; swapArray[1] = i; }
        else if(*dx != 0) { swapArray[0] = i; swapArray[1] = s; }

        if (s == 0) g = game->board[swapArray[0]][swapArray[1]];
        if (g == game->board[swapArray[0]][swapArray[1]]) m++;
    }
    if (m == 4 || m == 2) g = 2; else g = 1;

    // LOOP
    for (int s = 0; s < g; s++) {

        if (*dy == 1 || *dx == 1) d = matrixInt-1;
        else d = 0;
        // REPLACE
        while( ( (*dy == -1 || *dx == -1) && d < matrixInt) || ( (*dy == 1 || *dx == 1) && d >= 0) ) { // LEFT, UP || RIGHT, DOWN

            if (*dy != 0) { swapArray[0] = d; swapArray[1] = i; swapArray[2] = d+1; swapArray[3] = i; }
            else if(*dx != 0) { swapArray[0] = i; swapArray[1] = d; swapArray[2] = i; swapArray[3] = d+1; }

            if ((int)game->board[swapArray[0]][swapArray[1]] != 32 && matrixInt-1 > d && (int)game->board[swapArray[0]][swapArray[1]] == (int)game->board[swapArray[2]][swapArray[3]]) {
                game->board[swapArray[0]][swapArray[1]] += 1;
                game->board[swapArray[2]][swapArray[3]] = ' ';
                update_score(game, game->board[swapArray[0]][swapArray[1]]);

                retrn = true;
                break;
            }
            if ((*dy == 1 || *dx == 1)) d--;
            else d++;
        }

    }
    return retrn;
}

/**
 * Function updating matrix for fixed position
 * @param game reference to the game object
 * @param swapArray determined index of arrays
 */
bool update_matIf(GAME *game, int swapArray[]) {
    if ((int)game->board[swapArray[3]][swapArray[4]] >= 65) {
        game->board[swapArray[0]][swapArray[1]] = game->board[swapArray[3]][swapArray[4]];
        game->board[swapArray[3]][swapArray[4]] = ' ';
        return true;
    }
    return false;
}

/**
 * Function updating matrix given the direction
 * @param game reference to the game object
 * @param i is column of matrix
 * @param dy movement in y-axe
 * @param dx movement in x-axe
 */
bool update_matrix_walk(GAME *game, int i, int *dy, int *dx) {
     int matrixInt = MATRIX;
     int swapArray[10]; bool retrn = false;

    // ALL UPDATE
    if (*dy == -1 || *dx == -1) // FOR LEFT, UP
        for (int s = 0; s < matrixInt; s++) {
            //printf("S: %d\n", s);
            if (*dy != 0) { swapArray[0] = s; swapArray[1] = i;}
            else if(*dx != 0) { swapArray[0] = i; swapArray[1] = s;}

            // UPDATE
            if ((int)game->board[swapArray[0]][swapArray[1]] == 32) {
                for (int d = s; d < matrixInt; d++) {

                    if (*dy != 0) { swapArray[3] = d; swapArray[4] = i; }
                    else if(*dx != 0) { swapArray[3] = i; swapArray[4] = d; }

                    if (update_matIf(game, swapArray)) { retrn = true; break; }

                }
            }
        }

    else if (*dy == 1 || *dx == 1) // FOR RIGHT, DOWN
        for (int s = matrixInt-1; s >= 0; s--) {

            if (*dy != 0) { swapArray[0] = s; swapArray[1] = i; }
            else if(*dx != 0) { swapArray[0] = i; swapArray[1] = s; }

            // UPDATE
            if ((int)game->board[swapArray[0]][swapArray[1]] == 32) {
                for (int d = matrixInt-1-((matrixInt-1)-s+1); d >= 0; d--) {

                    if (*dy != 0) { swapArray[3] = d; swapArray[4] = i; }
                    else if(*dx != 0) { swapArray[3] = i; swapArray[4] = d; }

                   if (update_matIf(game, swapArray)) { retrn = true; break; }
                }
            }
        }

    return retrn;
}

// MAGIC FUNCTION from k.h
bool update(GAME *game, int dy, int dx) {

    if ( !(dx == 0 && dy != 0) && !(dx != 0 && dy == 0)) return false;

    int matrixInt = MATRIX;
    bool returns = false, retrn = false;

    for (int i = 0; i < matrixInt; i++) {

        // UPDATE
        retrn = update_matrix_walk(game, i, &dy, &dx);
        if (retrn && !returns) returns = true;
        // REPLACE
        retrn = replace_matrix(game, i, &dy, &dx);
        if (retrn && !returns) returns = true;
        // AGAIN UPDATE
        update_matrix_walk(game, i, &dy, &dx);

    }

    return returns;
}
