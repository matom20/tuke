//
//  playfair.c
//  top-secret-ps5-my
//
//  Created by Martin M. on 7.5.2015.
//  Last Edit by Martin M. on 18.5.2015.
//  Copyright (c) 2015 Martin M. All rights reserved.
//  xCode 7.x
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "playfair.h"

#define alphabet "ABCDEFGHIJKLMNOPQRSTUVXYZ";
#define matrixDef 5;

/**
 * Function find char in the text
 * @param text
 * @param find - find character
 * @param position - position for loop
 * @return bool - true -> if exist, false - if not exist
 */
bool is_char(const char* text, const char find, int position, const int size) {
    for (int i = 0; i < size; i++) {
        if (position != -1 && i == position) continue;
        if (text[i] == find) return true;
    }
    return false;
}

/**
 * Function change characters to uppercase
 * @param text list of characters
 * @return string uppercase
 */
void strupr_p (char *text) {
    while (*text != '\0') {
        if (islower(*text)) *text &= ~0x20;
        text++;
    }
}

/**
 * Function characters to copy with malloc
 * @param text
 * @return string
 */
char* strdup_p (const char *s) {
    char* d = (char*)malloc((strlen(s) + 1) * sizeof(char));
    if (d != NULL) strcpy(d, s);
    return d;
}


/**
 * Function unset char from array string
 * @param text - string for text
 * @param garbage - char for deleted
 */
void removeChar(char *str, char garbage) {
    char *src, *dst;
    for (src = dst = str; *src != '\0'; src++) {
        *dst = *src;
        if (*dst != garbage) dst++;
    }
    *dst = '\0';
}

/**
 * Function add x for key
 * @param text - string for text
 * @param position for add X
 */
void add_x(char* text, const int position, const int size) {
    int i;
    for (i = size; i >= 0; i--) {
        if (i == position) {
            text[i] = 'X';
            break;
        } else
            text[i] = text[i-1];
    }
    text[size+1] = '\0';
}

/**
 * Function replace character for word
 * @param text - string for text
 * @param find char in text
 * @param replace char from find
 */
void replace_char(char* text, const char find, const char replace) {
    if (is_char(text, find, -1, (int)strlen(text))) {
        for (int i = 0; i < (int)strlen(text); i++) {
            if (text[i] == find)
                text[i] = replace;
        }
    }
}

/**
 * Function create matrix for playfair
 * @param alloc matrix
 * @param word for added matrix
 */
void createMatrix(char** matrix, const char* word) {
    int d = 0;
    int defMatrix = matrixDef;
    for (int i = 0; i < defMatrix; i++) {
        matrix[i] = (char*)malloc(defMatrix+1 * sizeof(char));
        for (int s = 0; s < defMatrix; s++) {
            matrix[i][s] = word[d];
            d++;
        }
    }

}


// MAGIC FUNCTION IN playfair.h
char* playfair_encrypt(const char* key, const char* text) {
    if (key == NULL || text == NULL) return NULL;
    if ((int)strlen(key) < 1) return NULL;

    int defMatrix = matrixDef;
    char* new_key = strdup_p(key);

    char* word = (char*)malloc((defMatrix*defMatrix)+1 * sizeof(char));
    if (word == NULL) {
        free(new_key);
        return NULL;
    }

    // UP KEY
    strupr_p(new_key);

    // REPLACE W FOR KEY
    replace_char(new_key, 'W', 'V');


    int keyLen = (int)strlen(new_key);
    int minus = 0;
    // REPLACE the same CHAR FOR KEY
    for (int i = (keyLen-1); i >= 0; i--)
        if (is_char(new_key, new_key[i], i, (int)strlen(new_key))) {
            minus++;
            new_key[i] = ' ';
        }
    removeChar(new_key, ' ');
    keyLen = keyLen - minus + 1;
    new_key[keyLen] = '\0';

    // ADD OTHER CHAR
    strcpy(word, new_key);
    char spelling[] = alphabet;
    for (int i = 0, s = (int)strlen(new_key); i < 25; i++) {
        if (!is_char(word, spelling[i], -1, s)) {
            word[s] = spelling[i];
            s++;
        }
    }
    word[25] = '\0';

    // MATRIX
    char** matrix = (char**)malloc(defMatrix * sizeof(char*));
    if (matrix == NULL) return NULL;
    createMatrix(matrix, word);

    // ALLOC FOR NEW TEXT
    int textLen = (int)strlen(text);
    int d = 0;
    for (int i = 0; i < textLen; i += 2) if (text[i] == text[i+1] && text[i+1] != 'X') d++;

    char* dest = (char*)malloc((textLen + d)+1 * sizeof(char));
    if (dest == NULL) {
        free(word);
        free(new_key);
        for (int i = 0; i < defMatrix; i++) free(matrix[i]);
        free(matrix);
        return NULL;
    }

    strcpy(dest, text);

    removeChar(dest, ' ');
    strupr_p(dest);


    // REPLACE W FOR TEXT
    replace_char(dest, 'W', 'V');

    // ADD 'X' FOR TEXT
    for (int i = 0; i < textLen; i += 2) {
        if (dest[i] == dest[i+1] && dest[i+1] != 'X') {
            add_x(dest, i+1, textLen);
        }
    }

    // ODD ADD X
    int destLen = (int)strlen(dest);
    if (!(destLen % 2 == 0)) {
        dest[destLen] = 'X';
        dest[destLen+1] = '\0';
    }

    // ENCRYPT
    int* first = (int*)malloc(2 * sizeof(int));
    int* second = (int*)malloc(2 * sizeof(int));

    int countDest = 0;
    char* returnDest = (char*)malloc(((int)strlen(dest)+1) * sizeof(char));
    int retDest = 0;

    while (dest[countDest] != '\0') {

        // SEARCH MATRIX FIRST AND SECOND
        for (int i = 0; i < defMatrix; i++) {
            for (int s = 0; s < defMatrix; s++) {
                // FIRST
                if ((int)dest[countDest] == (int)matrix[i][s]) {
                    first[0] = i;
                    first[1] = s;
                }
                // SECOND
                if (dest[countDest+1] == matrix[i][s]) {
                    second[0] = i;
                    second[1] = s;
                }

            }
        }

        countDest += 2;

        if (first[0] != second[0] && first[1] != second[1]) { // FIRST RULE COL != ROW
            returnDest[retDest++] = matrix[first[0]][second[1]];
            returnDest[retDest++] = matrix[second[0]][first[1]];

        } else if (first[0] == second[0] && first[1] != second[1]) { // IF ROW ==
            int f = (first[1] == defMatrix-1 ? 0 : first[1]+1);
            int sec = (second[1] == defMatrix-1 ? 0 : second[1]+1);

            returnDest[retDest++] = matrix[first[0]][f];
            returnDest[retDest++] = matrix[second[0]][sec];


        } else if ((first[0] != second[0] && first[1] == second[1]) || (first[0] == second[0] && first[1] == second[1])) { // IF COL == AND IF ROW == COL - FIRST AND SECOND
            int f = (first[0] == defMatrix-1 ? 0 : first[0]+1);
            int sec = (second[0] == defMatrix-1 ? 0 : second[0]+1);

            returnDest[retDest++] = matrix[f][first[1]];
            returnDest[retDest++] = matrix[sec][second[1]];
        }
    }

    returnDest[retDest] = '\0';
    free(first);
    free(second);


    free(word);
    free(new_key);
    for (int i = 0; i < defMatrix; i++) free(matrix[i]);
    free(matrix);
    free(dest);

    return returnDest;
}

// MAGIC FUNCTION IN playfair.h
char* playfair_decrypt(const char* key, const char* text) {
    if (key == NULL || text == NULL) return NULL;
    if ((int)strlen(key) < 1) return NULL;

    if (is_char(text, 'W', -1, (int)strlen(text))) return NULL;

    int defMatrix = matrixDef;
    char* new_key = strdup_p(key);

    char* word = (char*)malloc((defMatrix*defMatrix)+1 * sizeof(char));
    if (word == NULL) {
        free(new_key);
        return NULL;
    }

    // UP KEY
    strupr_p(new_key);

    // REPLACE W FOR KEY
    replace_char(new_key, 'W', 'V');


    int keyLen = (int)strlen(new_key);
    int minus = 0;
    // REPLACE the same CHAR FOR KEY
    for (int i = (keyLen-1); i >= 0; i--)
        if (is_char(new_key, new_key[i], i, (int)strlen(new_key))) {
            minus++;
            new_key[i] = ' ';
        }
    removeChar(new_key, ' ');
    keyLen = keyLen - minus + 1;
    new_key[keyLen] = '\0';

    // ADD OTHER CHAR
    strcpy(word, new_key);
    char spelling[] = alphabet;
    for (int i = 0, s = (int)strlen(new_key); i < 25; i++) {
        if (!is_char(word, spelling[i], -1, s)) {
            word[s] = spelling[i];
            s++;
        }
    }
    word[25] = '\0';

    // MATRIX
    char** matrix = (char**)malloc(defMatrix * sizeof(char*));
    if (matrix == NULL) return NULL;
    createMatrix(matrix, word);

    // ALLOC FOR NEW TEXT
    int textLen = (int)strlen(text);
    char* dest = (char*)malloc(textLen+1 * sizeof(char));
    if (dest == NULL) {
        free(word);
        free(new_key);
        for (int i = 0; i < defMatrix; i++) free(matrix[i]);
        free(matrix);
        return NULL;
    }

    strcpy(dest, text);
    removeChar(dest, ' ');

    // DECRYPT
    int* first = (int*)malloc(2 * sizeof(int));
    int* second = (int*)malloc(2 * sizeof(int));

    int countDest = 0;
    char* returnDest = (char*)malloc(((int)strlen(dest)+1) * sizeof(char));
    int retDest = 0;

    while (dest[countDest] != '\0') {
        // SEARCH MATRIX FIRST AND SECOND
        for (int i = 0; i < defMatrix; i++) {
            for (int s = 0; s < defMatrix; s++) {
                // FIRST
                if ((int)dest[countDest] == (int)matrix[i][s]) {
                    first[0] = i;
                    first[1] = s;
                }
                // SECOND
                if (dest[countDest+1] == matrix[i][s]) {
                    second[0] = i;
                    second[1] = s;
                }

            }
        }

        countDest += 2;

        if (first[0] != second[0] && first[1] != second[1]) { // FIRST RULE COL != ROW
            returnDest[retDest++] = matrix[first[0]][second[1]];
            returnDest[retDest++] = matrix[second[0]][first[1]];

        } else if (first[0] == second[0] && first[1] != second[1]) { // IF ROW ==
            int f = (first[1] == 0 ? defMatrix-1 : first[1]-1);
            int sec = (second[1] == 0 ? defMatrix-1 : second[1]-1);

            returnDest[retDest++] = matrix[first[0]][f];
            returnDest[retDest++] = matrix[second[0]][sec];

        } else if ((first[0] != second[0] && first[1] == second[1]) || (first[0] == second[0] && first[1] == second[1])) {  // IF COL == AND IF ROW == COL - FIRST AND SECOND
            int f = (first[0] == 0 ? defMatrix-1 : first[0]-1);
            int sec = (second[0] == 0 ? defMatrix-1 : second[0]-1);

            returnDest[retDest++] = matrix[f][first[1]];
            returnDest[retDest++] = matrix[sec][second[1]];
        }

    }
    returnDest[retDest] = '\0';
    free(first);
    free(second);


    free(word);
    free(new_key);
    for (int i = 0; i < defMatrix; i++) free(matrix[i]);
    free(matrix);
    free(dest);
    return returnDest;

}
