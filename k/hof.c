#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "hof.h"

#define HOF_FILE "score"

// MAGIC FUNCTION from hof.h
int load(PLAYER list[]){
    // open the hall of fame file
    FILE *fp = fopen(HOF_FILE, "r");
    if(fp == NULL){
        return -1;
    }
    
    // read the content of hall of fame
    int idx = 0;
    while(fscanf(fp, "%29s %d", list[idx].name, &list[idx].score) != EOF && idx < 10){
        idx++;
    }
    
    fclose(fp);
    return idx;
}

// MAGIC FUNCTION from hof.h
bool save(const PLAYER list[], const int size){
    FILE *fp = fopen(HOF_FILE, "w");
    if(fp == NULL){
        return false;
    }
    
    // save the content of the list
    for(int idx = 0; idx < size && idx < 10; idx++){
        fprintf(fp, "%s %d\n", list[idx].name, list[idx].score);
    }
    
    fclose(fp);
    return true;
}

/**
 * Function swap list
 * @param score array
 * @param name array
 * @param position is index of array
 */
void listSwap(int *new_score, char **new_name, const int position) {
    int score = new_score[position];
    
    char* name = (char*)malloc((strlen(new_name[position])+1) * sizeof(char));
    strcpy(name, new_name[position]);
    
    new_score[position] = new_score[position+1];
    
    free(new_name[position]);
    new_name[position] = (char*)malloc((strlen(new_name[position+1])+1) * sizeof(char));
    strcpy(new_name[position], new_name[position+1]);
    
    new_score[position+1] = score;
    
    free(new_name[position+1]);
    new_name[position+1] = (char*)malloc((strlen(name)+1) * sizeof(char));
    strcpy(new_name[position+1], name);
    
    free(name);
}

/**
 * Function free's
 */
void freeFF(char **name, int *score, const int size) {
    for(int i = 0; i < size; i++) free(name[i]);
    free(name);
    free(score);
}

/**
 * Function compare for qsort
 */
int compare_add_player (const void * a, const void * b){
    return strcmp(*((char**) a), *((char**) b));
}

// MAGIC FUNCTION from hof.h
bool add_player(PLAYER list[], int* size, const PLAYER player) {
    if (*size == -1) return false;
    int yes_11;
    
    char **new_name = (char**)malloc((*size+1) * sizeof(char*));
    int* new_score = malloc((*size+1) * sizeof(int));
    
    if (*size >= 1) {
        for (int i = 0; i < *size; i++) {
            new_name[i] = (char*)malloc((strlen(list[i].name)+1) * sizeof(char));
            strcpy(new_name[i], list[i].name);
            new_score[i] = list[i].score;
        }
    }
    
    // ADD NEW PLAYER
    new_name[*size] = (char*)malloc((strlen(player.name)+1) * sizeof(char));
    strcpy(new_name[*size], player.name);
    new_score[*size] = player.score;
    
    *size += 1;
    
    if (*size > 1) {
        
        // SORT FOR SCORE
        for (int i = 0; i < *size; i++)
            for (int s = 0; s < (*size-1); s++)
                if (new_score[s] < new_score[s+1]) listSwap(new_score, new_name, s);
        
        // SORT FOR NAME
        char ** arrays = (char**)malloc(2 * sizeof(char*));
        for (int g = 0; g < *size; g++)
            for (int s = 0; s < (*size-1); s++)
                if (new_score[s] == new_score[s+1]) {
                    
                    arrays[0] = (char*)malloc((strlen(new_name[s])+1) * sizeof(char));
                    strcpy(arrays[0], new_name[s]);
                    
                    arrays[1] = (char*)malloc((strlen(new_name[s+1])+1) * sizeof(char));
                    strcpy(arrays[1], new_name[s+1]);
                    
                    qsort(arrays, 2, sizeof(char **), compare_add_player);
                    if (strcmp(new_name[s], arrays[0]) != 0) listSwap(new_score, new_name, s);
                    free(arrays[0]);
                    free(arrays[1]);
                }
        free(arrays);
        
    }
    
    yes_11 = *size;
    if (*size >= 10) {
        if (strcmp(new_name[*size-1], new_name[*size-2]) == 0 && new_score[*size-1] == new_score[*size-2]) {
            freeFF(new_name, new_score, yes_11);
            return false;
        }
        *size = 10;
    }
    
    for (int i = 0; i < *size; i++) {
        list[i].score = new_score[i];
        strcpy(list[i].name, new_name[i]);
    }
    
    // REMOVING NAME, SCORE FROM MEMORY
    freeFF(new_name, new_score, yes_11);
    
    if (*size < 10) {
        save(list, *size);
        return true;
    }
    
    // SEARCH LIST
    for (int i = 0; i < *size; i++) {
        if (strcmp(list[i].name, player.name) == 0 && list[i].score == player.score) {
            save(list, *size);
            return true;
        }
    }
    
    return false;
}

/**
 * Function show place from list/score file
 * @param actual player
 * @param list from score file
 * @param size the real size of entries in list
 * @return number of the list
 */
int placeInList(PLAYER player, PLAYER list[], const int size) {
    int place = 0;
    for (int i = 0; i < size; i++) {
        place++;
        if (strcmp(list[i].name, player.name) == 0 && list[i].score == player.score) break;
    }
    return place;
}
