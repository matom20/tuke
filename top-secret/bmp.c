//
//  bmp.c
//  top-secret-ps5-my
//
//  Created by Martin M. on 7.5.2015.
//  Last Edit by Martin M. on 18.5.2015.
//  Copyright (c) 2015 Martin M. All rights reserved.
//  xCode 7.x
//

#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"
#include <ctype.h>
#include <string.h>

/**
 * Function change characters to uppercase
 * @param text list of characters
 * @return string uppercase
 */
void strupr(char *text) {
    while (*text != '\0') {
        if (islower(*text)) *text &= ~0x20;
        text++;
    }
}
/**
 * Function change characters to string reverse
 * @param text list of characters
 * @return string reversed
 */
char* strrev(char *str) {
    char *p1, *p2;

    if (!str || !*str) return str;
    for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2) {
        *p1 ^= *p2;
        *p2 ^= *p1;
        *p1 ^= *p2;
    }
    return str;
}

/**
 * Function characters to copy with malloc
 * @param text
 * @return string
 */
char* strdup (const char *s) {
    char* d = (char*)malloc((strlen(s) + 1) * sizeof(char));
    if (d != NULL) strcpy(d, s);
    return d;
}

// MAGIC FUNCTION IN bmp.h
char* reverse(const char* text) {
    if (text == NULL) return NULL;
    char* newString = strdup(text);
    strupr(newString);
    strrev(newString);
    return newString;
}

// MAGIC FUNCTION IN bmp.h
char* vigenere_encrypt(const char* key, const char* text) {
    if (key == NULL || text == NULL) return NULL;

    char* dest = strdup(text);
    char* keys = strdup(key);
    strupr(dest);
    strupr(keys);

    int slen = (int)strlen(dest);
    int klen = (int)strlen(keys);

    for (int i = 0, d = 0; i < slen; i++) {
        if (!(dest[i] >= 'A' && dest[i] <= 'Z')) continue;
        dest[i] = 'A' + (dest[i] - 'A' + keys[d % klen] - 'A') % 26;
        d++;
    }

    free(keys);
    return dest;
}

// MAGIC FUNCTION IN bmp.h
char* vigenere_decrypt(const char* key, const char* text) {
    if (key == NULL || text == NULL) return NULL;

    char* dest = strdup(text);
    char* keys = strdup(key);
    strupr(dest);
    strupr(keys);

    int klen = (int)strlen(keys);
    int slen = (int)strlen(dest);

    for (int i = 0, d = 0; i < slen; i++) {
        if (!(dest[i] >= 'A' && dest[i] <= 'Z')) continue;
        dest[i] = 'A' + (dest[i] - keys[d % klen] + 26) % 26;
        d++;
    }

    free(keys);
    return dest;
}

// MAGIC FUNCTION IN bmp.h
char* bit_encrypt(const char* text) {
    if (text == NULL) return NULL;

    char* binary = strdup(text);

    int i = 0;

    unsigned char binar1;
    unsigned char binar2;
    unsigned char new_bit;

    while (text[i] != '\0') {

        // 4 BIT 1000 -> 0100
        if ((binary[i] >> 4 & 0xf4) == 0x00 || (binary[i] >> 4 & 0xf4) == 0xc)
            binar1 = (binary[i] >> 4 & 0xf4);
        else
            binar1 = ((binary[i] >> 4 & 0xf4) ^ 0x0c);

        // 4 BIT 0010 -> 0001
        if ((binary[i] >> 4 & 0x13) == 0x0 || (binary[i] >> 4 & 0x13) == 0x3)
            binar2 = ((binary[i] >> 4 & 0x13));
        else
            binar2 = ((binary[i] >> 4 & 0x13) ^ 0x3);

        binar1 ^= binar2;
        binar2 = (binary[i] << 4 ^ binar1 << 4);
        new_bit = binar1 << 4 ^ binar2 >> 4;

        binary[i] = new_bit;
        i++;
    }
    return binary;
}

// MAGIC FUNCTION IN bmp.h
char* bit_decrypt(const char* text) {
    if (text == NULL) return NULL;

    char* binary = (char*)malloc((strlen(text)+1) * sizeof(char));
    if (binary == NULL) return NULL;
    strcpy(binary, text);

    unsigned char binar1;
    unsigned char binar2;
    unsigned char binar3;
    unsigned char new_bit;
    unsigned char binar_d;

    int i = 0;
    while (text[i] != '\0') {
        binar1 = binary[i] & 0xf0;
        binar2 = binary[i] << 4;

        binar1 ^= binar2;
        binar1 >>= 4;

        binar_d = binary[i] >> 4 & 0x0f;

        // 4 BIT 1000 -> 0100
        if ((binar_d & 0xfc) == 0x00 || (binar_d & 0xfc) == 0xc)
            binar2 = (binar_d & 0xfc);
        else
            binar2 = ((binar_d & 0xfc) ^ 0x0c);

        // 4 BIT 0010 -> 0001
        if ((binar_d & 0xf3) == 0x0 || (binar_d & 0xf3) == 0x3)
            binar3 = ((binar_d & 0xf3));
        else
            binar3 = ((binar_d & 0xf3) ^ 0x3);


        binar2 ^= binar3;
        new_bit = binar1 ^ binar2 << 4;
        binary[i] = new_bit;
        i++;
    }

    return binary;
}

// MAGIC FUNCTION IN bmp.h
char* bmp_encrypt(const char* key, const char* text) {
    if (key == NULL || text == NULL) return NULL;

    char* dest = (char*)malloc(((int)strlen(text)+1) * sizeof(char));
    if (dest == NULL) return NULL;

    char* rev = reverse(text);
    char* vig = vigenere_encrypt(key, rev);
    char* bit = bit_encrypt(vig);

    strcpy(dest, bit);

    free(vig);
    free(bit);
    free(rev);

    return dest;
}

// MAGIC FUNCTION IN bmp.h
char* bmp_decrypt(const char* key, const char* text) {
    if (key == NULL || text == NULL) return NULL;

    char* dest = (char*)malloc(((int)strlen(text)+1) * sizeof(char));
    if (dest == NULL) return NULL;

    char* bit = bit_decrypt(text);
    char* vig = vigenere_decrypt(key, bit);
    char* rev = reverse(vig);

    strcpy(dest, rev);

    free(vig);
    free(bit);
    free(rev);

    return dest;
}
