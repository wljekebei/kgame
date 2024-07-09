#include <stdio.h>
#include <stdlib.h>
#include "hof.h"
#include <time.h>
#include <string.h>

int load(struct player list[]) {
    FILE *f = fopen(HOF_FILE, "r");
    if (f == NULL) {
        printf("Error: Can not open HOF file");
        return -1;
    }
    int entries = 0;
    char c = 'c';
    int i = 0;
    while (c != EOF && entries < 10) {
        int j = 0;
        while ((c = fgetc(f)) != DELIMITER && c != EOF) { 
            list[i].name[j] = c;
            j++;
        }
        list[i].name[j] = '\0';
        j = 0;
        char cnum[10];
        int num = 0;
        int k = 1;
        while ((c = fgetc(f)) != '\n' && c != EOF) { 
            cnum[j] = c;
            j++;
        }
        cnum[j] = '\0';
        for (int j = (strlen(cnum) - 1); j >= 0; j--) {
            num += k * (cnum[j] - 48);
            k *= 10;
        }
        list[i].score = num;
        i++;
        entries++;
    }
    fclose(f);
    return entries;
}

bool save(const struct player list[], const int size) {
    int slist[10];
    for (int i = 0; i < size; i++) {
        slist[i] = list[i].score;
    }
    FILE *f = fopen(HOF_FILE, "w");
    for (int i = 0; i < size; i++) {
        int max = slist[0];
        int maxIndex = 0;
        for (int j = 0; j < size; j++) {
            if (slist[j] > max) {
                maxIndex = j;
                max = slist[j];
            }
        }
        if (i != size - 1) {
            fprintf(f, "%s %d\n", list[maxIndex].name, list[maxIndex].score);
            slist[maxIndex] -= slist[maxIndex];
        } else {
            fprintf(f, "%s %d", list[maxIndex].name, list[maxIndex].score);
            slist[maxIndex] -= slist[maxIndex];
        }
    }
    fclose(f);
    return 1;
}

bool add_player(struct player list[], int* size, const struct player player) {
    if (*size < 10) {
        list[*size+1].score = player.score;
    }
    for (int i = 0; i < *size; i++) {
        if (player.score >= list[i].score) {
            list[(*size)-1] = player;
            (*size)++;
            if (save(list, *size)) {
                printf("Your best score was added to HOF list!\n");
                return 1;
            }
        } else if ((*size) < 10) {
            list[(*size)] = player;
            printf("before: %d\n", *size);
            (*size)++;
            printf("after: %d\n", *size);
            if (save(list, *size)) {
                printf("Your score was added to HOF list!\n");
                return 1;
            }
        }
    }
    return 0;
}