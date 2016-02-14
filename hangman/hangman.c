#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include "hangman.h"
#include "figure.h"


#define numGUESSES 8 // MAX GUESS
#define allLetters "abcdefghijklmnopqrstuvwxyz"
#define maxLetter 15 // MAX CHARACTER WORD
#define onFigure true // ON/OFF FIGURE - IF TRUE PLEASE UNCOMMENTED INCLUDE!!!

void separator() { printf("\n-------------\n"); }

// MAGIC FUNCTION FOR GET WORD TO SECRET VAR "hangman.h"
int getWord(char secret[]){
    // check if file exists first and is readable
    FILE *fp = fopen(WORDLIST_FILENAME, "rb");
    if( fp == NULL ){
        fprintf(stderr, "No such file or directory: %s\n", WORDLIST_FILENAME);
        return 1;
    }

    // get the filesize first
    struct stat st;
    stat(WORDLIST_FILENAME, &st);
    long int size = st.st_size;

    do{
        // generate random number between 0 and filesize
        long int random = (rand() % size) + 1;
        // seek to the random position of file
        fseek(fp, random, SEEK_SET);
        // get next word in row ;)
        int result = fscanf(fp, "%*s %20s", secret);
        if( result != EOF ) break;
    } while(1);

    fclose(fp);

    return 0;
}


/**
 * Function change characters to lowercase
 * @param text list of characters
 * @return string lowercase
 */
char *toLowerCase(const char text[]) {
    int length = (int) strlen(text);
    char *result = malloc(length);
    for (int i = 0; i < length; i++)
        if ((text[i] >= 65) && (text[i] <= 90))
            result[i] = text[i] | 32;
        else
            result[i] = text[i];
    return result;
}

/**
 * Function finding charakters in string
 * @param text list of characters
 * @param find character finding in list
 * @return status search; 1 - true find, 2 - false
 */
int searchLetter(const char text[], const char *find){
    int count = 0;
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] == *find) {
            count++;
            break;
        }
    }
    if (count != 0) return 1; else return 0;
}

// MAGIC FUNCTION "hangam.h"
void getAvailableLetters(const char lettersGuessed[], char availableLetters[]) {
    strcpy(availableLetters, allLetters);
    char copy[256];
    int i = 0, c = 0;
    memset(copy, '\0', sizeof(copy));
    while (availableLetters[i] != '\0') {
        if (!searchLetter(lettersGuessed, &availableLetters[i])) {
            strcpy(&copy[c], &availableLetters[i]);
            c++;
        }
        i++;
    }
    copy[c] = '\0';
    strcpy(availableLetters, copy);
}

// MAGIC FUNCTION "hangam.h"
void getGuessedWord(const char secret[], const char lettersGuessed[], char guessedWord[]) {
    for (int i = 0; secret[i] != '\0'; i++) {
        if (searchLetter(lettersGuessed, &secret[i]) == 1) {
            strcpy(&guessedWord[i], &secret[i]);
        } else  strcpy(&guessedWord[i], "_");
    }
}

// MAGIC FUNCTION "hangam.h"
int isWordGuessed(const char secret[], const char lettersGuessed[]) {
    for (int i = 0; secret[i] != '\0'; i++)
        if (searchLetter(lettersGuessed, &secret[i]) == 0) return 0;
    return 1;
}

/**
 * Function which stores the lettersGuessed characters added from scanf
 * @param input characters add for lettersGuessed
 * @param lettersGuessed the lowercase letters player already used in his guessing
 */
void setLettersGuessed(char input[], char lettersGuessed[]) {
    int inputLen = (int) strlen(input);
    int letterLen = (int) strlen(lettersGuessed);

    if (letterLen == 0) strcpy(lettersGuessed, input);
    else {
         if (inputLen == 1) {
             for (int i = 0; i < inputLen; i++, letterLen++) {
                if (searchLetter(lettersGuessed, &input[i]) == 0)
                    strcpy(&lettersGuessed[letterLen], &input[i]);
            }
         } else strcpy(lettersGuessed, input);
    }
    // free(input);
}

// MAGIC FUNCTION "hangam.h"
void hangman(const char secret[]) {

    char lettersGuessed[256] = "";
    char availableLetters[256];
    char guessedWord[256];
    char lettersGuessedLast[256] = "";

    int maxLetters = maxLetter;
    if (maxLetters > 200) maxLetters = 200;


    char addLetter[256];
    char *addLetterLow;

    int figur = 0; // UNCOMMENTED FOR FIGURE

    // WELCOME
    printf("Welcome to the game, Hangman!\n");

    // STRLEN FOR LETTER
    int lettersLong = (int) strlen(secret);
    printf("I am thinking of a word that is %d letters long.", lettersLong);
    //printf("\nsecret: %s", secret); /// ... WARNING - DELETE  ......
    separator();

    int numGuess = numGUESSES;
    bool onFigureBool = onFigure; // UNCOMMENTED FOR FIGURE

    while(1) {
        figur = 0; // UNCOMMENTED FOR FIGURE
        // NUM GUESS
        printf("You have %d guesses left.", numGuess);

        // AVIABLE LETTERS
        getAvailableLetters(lettersGuessed, availableLetters);
        printf("\n");
        printf("Available letters: %s\n", availableLetters);

        // WRITING USER
            // USER ADD LETTER
            printf("Please guess a letter: ");
            scanf("%20s", addLetter);

            // if you write more words
            int strLenLetAdd = (int)strlen(addLetter);
            if (strLenLetAdd > maxLetters) addLetter[maxLetters] = '\0';

            // IF "addLetter" is num
            if (strLenLetAdd == 1 && (int)addLetter[0] >= 48 && (int)addLetter[0] <= 57) {
                printf("Sorry, bad guess. The word was %s.\n", secret);
                break;
            }

            // LETTER TO LOWER
            addLetterLow = toLowerCase(addLetter);

        // SET GUESS
        strcpy(lettersGuessedLast, lettersGuessed);
        setLettersGuessed(addLetterLow, lettersGuessed);


        // IF WRITING WORD
        if (strLenLetAdd >= 2) {
            if (isWordGuessed(secret, lettersGuessed) && strLenLetAdd == lettersLong) {
                printf("Congratulations, you won!\n");
                break;
            } else {
                if (onFigureBool) { // UNCOMMENTED FOR FIGURE
                    getFigure(-1);
                    printf("\n");
                }
                printf("Sorry, bad guess. The word was %s.\n", secret);
                break;
            }
        }

            // IF GUESS CHARACETER OR NOT - WRITING TEXT - printf
                if (searchLetter(secret, addLetterLow) == 1 && !searchLetter(lettersGuessedLast, addLetterLow))
                        printf("Good guess:");
                else if (searchLetter(lettersGuessedLast, addLetterLow))
                        printf("Oops! You've already guessed that letter:");
                else {
                        printf("Oops! That letter is not in my word:");
                    if (!searchLetter(lettersGuessedLast, addLetterLow)) numGuess--;
                    figur = 1; // UNCOMMENTED FOR FIGURE
                }

        // GET WORD FROM LETTER/SECRET
        getGuessedWord(secret, lettersGuessed, guessedWord);
        for (int i = 0; guessedWord[i] != '\0'; i++) printf(" %c", guessedWord[i]);

        if (figur == 1 && onFigureBool) getFigure(numGuess); // UNCOMMENTED FOR FIGURE

        separator();

        if (isWordGuessed(secret, lettersGuessed)) {
            printf("Congratulations, you won!\n");
            break;
        }

        if (numGuess <= 0) {
            printf("Sorry, you ran out of guesses. The word was %s.\n", secret);
            break;
        }

    }
}
