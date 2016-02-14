
#include <stdio.h>
#include "figure.h"

/**
 * Function returns char for figure
 * @param body - actual body for figure
 */
void figurePrint(char body[200]) {
    for (int s = 0; s < 5; s++) {
        if (body[s] == 't') printf("\t");
        else if (body[s] == 'n') printf("\n");
        else if (body[s] == 'b') printf("%c ", (char)92);
        else printf("%c", body[s]);
    }
}

/**
 * Function returns string figure for hangman
 * @param guess - actual guess on hangman
 */
void getFigure(int guess) {
    if (guess != -1) printf("\n");
    printf("Figure:\n");

    /*   const char body[][200] = {
     {' ', '|', 't', ' ', 'O', ' ', 'n'},
     //  {'t', ' ', '|', ' ', 'n'},
     //  {'t', '/', '|', ' ', 'n'}
     {' ', '|', 't', '/', '|', 'b', 'n'},
     {' ', '|', 't', ' ', '|', ' ', 'n'},
     {' ', '|', 't', '/', ' ', 'b', 'n'},
     };
     */

    char body[10][200] = {
        {'t', ' ', 'O', ' ', 'n'}, // 0
        {'t', ' ', '|', ' ', 'n'}, // 1
        {'t', '/', '|', ' ', 'n'}, // 2
        {'t', '/', '|', 'b', 'n'}, // 3
        {'t', ' ', '|', ' ', 'n'}, // 4
        {'t', '/', ' ', ' ', ' '}, // 5
        {'t', '/', ' ', 'b', ' '}, // 6
    };



    // printf(" ");
    for (int i = 0; i < 10; i++) printf("_");
    printf("\n");
    printf("\t #\n");

    switch (guess) {
        case 6:
            figurePrint(body[0]);
            break;
        case 5:
            figurePrint(body[0]);
            figurePrint(body[1]);
            break;
        case 4:
            figurePrint(body[0]);
            figurePrint(body[2]);
            break;
        case 3:
            figurePrint(body[0]);
            figurePrint(body[3]);
            break;
        case 2:
            figurePrint(body[0]);
            figurePrint(body[3]);
            figurePrint(body[4]);
            break;
        case 1:
            figurePrint(body[0]);
            figurePrint(body[3]);
            figurePrint(body[4]);
            figurePrint(body[5]);
            break;
        case 0:
        case -1:
            figurePrint(body[0]);
            figurePrint(body[3]);
            figurePrint(body[4]);
            figurePrint(body[6]);
            break;

        default:
            break;
    }

    // printf("----");
}
