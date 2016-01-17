//
//  main.c
//  top-secret-ps5-my
//
//  Created by Martin M. on 7.5.2015.
//  Last Edit by Martin M. on 18.5.2015.
//  Copyright (c) 2015 Martin M. All rights reserved.
//  xCode 7.x
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "playfair.h"
#include "bmp.h"

int main(int argc, const char * argv[]) {

    const char* slovo = "Pocalo mu byt uzko a rad by sa bol na slobodno dostat";
    const char* key = "iqxxl";

    // REVERSE
    char* reversed = reverse(slovo);
    printf("Reverse: %s\n\n", reversed);
    free(reversed);

// BIT
    // ECRYPT
    char* bit_encrypted;
    bit_encrypted = bit_encrypt(slovo);
    printf("bit encrypted: ");
    for(int i=0; i < (int)strlen(slovo);i++) {
        printf("%x ", (unsigned char) bit_encrypted[i]);
    }

    // DECRYPT
    char* bit_decrypted;
    bit_decrypted = bit_decrypt(bit_encrypted);
    printf("\nbit decrypted: ");
    for(int i=0; i < (int)strlen(slovo);i++) {
        printf("%c", (unsigned char) bit_decrypted[i]);
    }

    free(bit_decrypted);
    free(bit_encrypted);


// vigenere_encrypt, vigenere_descrypt
    char *vigenere_encrypted, *vigenere_decrypted;

    vigenere_encrypted = vigenere_encrypt(key, slovo);
    vigenere_decrypted = vigenere_decrypt(key, vigenere_encrypted);

    printf("\n\nvigenere_encrypt: %s\n", vigenere_encrypted);

    printf("vigenere_decrypt: %s\n", vigenere_decrypted);

    free(vigenere_decrypted);
    free(vigenere_encrypted);


// BMP

    // ENCRYPT
    printf("\nbmp_encrypt: ");
    char* bmp_encrypted;
    bmp_encrypted = bmp_encrypt(key, slovo);
    for(int i=0; i<(int)strlen(slovo);i++) {
        printf("%x ", (unsigned char) bmp_encrypted[i]);
    }

    // DECRYPT
    printf("\nbmp_decrypt: ");
    char* bmp_decrypted;
    bmp_decrypted = bmp_decrypt(key, bmp_encrypted);
    printf("%s\n\n", bmp_decrypted);

    free(bmp_encrypted);
    free(bmp_decrypted);

    // Playfair


        const char* k = "jagnfsmmgn";
        const char* s = "Tu v meste mame len jednu studnu z ktorej vsetci pijeme ale nam ta voda draho padne lebo v jednej diere za mestom byva drak s dvanastimi hlavami ktoremu kazdy den jednu panicku musia dat zozrat lebo ak by mu nedali nikoho by na tu studnu nepustil a museli by sme od smadu pohynut";

    // ENCRYPT
    char* play_encrypted;
    printf("\nplayfair_encrypt '%s' -> '%s' : ", k, s);
    play_encrypted = playfair_encrypt(k, s);
    printf("\nOUPUT: %s\n\n", play_encrypted);

    // DECRYPT
    char* play_decrypted;
    printf("\nplayfair_decrypt '%s' -> '%s' : ", k, play_encrypted);
    play_decrypted = playfair_decrypt(k, play_encrypted);
    printf("\nOUTPUT: %s", play_decrypted);

    free(play_encrypted);
    free(play_decrypted);

    printf("\n");

    return 0;
}
