#include <stdio.h>
#include <string.h>
#include <stdbool.h>
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
 * @param player list object
 * @param position is index of array
 */
void listSwap(PLAYER list[], int *position) {
    int score = list[*position].score;
    char name[30];
    strcpy(name, list[*position].name);

    list[*position].score = list[*position+1].score;
    strcpy(list[*position].name, list[*position+1].name);

    list[*position+1].score = score;
    strcpy(list[*position+1].name, name);
}

// MAGIC FUNCTION from hof.h
bool add_player(PLAYER list[], int* size, const PLAYER player) {
    // ADD NEW PLAYER
    strcpy(list[*size].name, player.name);
    list[*size].score = player.score;

    *size += 1;

    if (*size > 1) {

        for (int i = 0; i < *size; i++)
            for (int s = 0; s < (*size-1); s++)
                // SORT FOR SCORE
                if (list[s].score < list[s+1].score) listSwap(list, &s);

        // SORT FOR NAME
        for (int g = 0; g < *size; g++)
            for (int s = 0; s < (*size-1); s++)
                if (list[s].score == list[s+1].score)

                    for (int d = 0; d < (int)strlen(list[s].name); d++) {
                        if ((int)strlen(list[s+1].name)-1 < d) break;
                        if ((int)list[s].name[d] < (int)list[s+1].name[d]) listSwap(list, &s);
                    }

    }
    if (*size >= 10) *size = 10;
    return save(list, *size);
}
