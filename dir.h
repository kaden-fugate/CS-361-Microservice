#ifndef DIR_H
#define DIR_H

#define MAXDIRS 4096
#define MAXPEOPLE 8192

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"

struct dir{
    int num_ppl;
    char **people;
};

struct dir *init_dir();
struct dir **read_input(int*);
char *get_query();
int **matches(char *, struct dir **, int, int*);
void writeMatches(int **, int);

#endif