﻿#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "my_sort.h"
#include <ctype.h>
#include <string.h>

struct line {
    char* pointer = NULL;
    int length = 0;
};

/*!
    \author Alex Sergeechev aka funtalex
    \version 1.0
    \brief This function writes in file 3 versions of Gamlet

    Three versions of Gamlet:
    1)Sorted in alphabetical order
    2)Sorted in alphabetical order but compared starting from the end
    3)Original version of Gamlet
*/
int main() {
    FILE* gamlet_in = fopen("gamlet.txt", "r");
    FILE* gamlet_out = fopen("new_gamlet.txt", "w");
    fseek(gamlet_in, 0, SEEK_END);
    int file_size = ftell(gamlet_in);

    char* buffer = (char*)calloc(file_size, sizeof(char));

    //struct line* Index = (struct line*)calloc(4729, sizeof(char*) + sizeof(int)); // pointers on start of each line - 4729 lines
    struct line Index[4729];

    int num_lines = 0;

    for (int i = 0; i < file_size; i++) {
        if (buffer != NULL && (i == 0 || buffer[i - 1] == '\n')) {
            Index[num_lines].pointer = buffer + i;
            if (num_lines > 0) {
                Index[num_lines - 1].length = Index[num_lines].pointer - Index[num_lines - 1].pointer;
            }
            num_lines++;
        }
    
    }

    my_sort(&Index, 0, num_lines - 1, cmp_str_start);

    for (int i = 0; i < num_lines; i++) {
        fprintf(gamlet_out, "%s", Index[i].pointer);
    }
    fprintf(gamlet_out, "\n\n\n");

    my_sort(&Index, 0, num_lines - 1, cmp_str_end);

    for (int i = 0; i < num_lines; i++) {
        fprintf(gamlet_out, "%s", Index[i].pointer);
    }
    fprintf(gamlet_out, "\n\n\n");

    for (int i = 0; i < file_size; i++) {
        if (buffer != NULL)
            fputs(buffer, gamlet_out);
    }

    free(buffer);
    fclose(gamlet_in);
    fclose(gamlet_out);

    return 0;
}