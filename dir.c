#include "dir.h"

struct dir *init_dir(){

    struct dir *dir = malloc(sizeof(struct dir));
    dir->people = malloc( sizeof( char * ) * MAXPEOPLE );

    for(int i = 0; i < MAXPEOPLE; i++){ dir->people[i] = NULL; }

    return dir;
}

void printLine(char line[]){ printf("LINE: %s\n", line); }

char *get_query(){

    char filename[] = "pplinp.txt";
    FILE *file = fopen(filename, "r");
    char *line = malloc(256);

    // get user search
    fgets(line, 256, file);
    line[ strlen(line) - 1 ] = '\0';

    fclose(file);

    return line;
}

void printdir(struct dir *dir){ for(int i = 0; i < dir->num_ppl; i++){ printf("%s\n", dir->people[i]); } }

struct dir *read_dir(FILE *file, struct dir *dir){

    char line[4096];
    char skip[4096];

    // get num people in dir
    fgets(line, 4096, file);
    int dir_len = atoi( line + strlen(line) - 2 );

    dir = malloc( sizeof( struct dir ) );
    dir->num_ppl = dir_len;
    dir->people = malloc(sizeof(char*) * dir_len);

    for(int i = 0; i < dir_len; i++){

        // get person
        fgets(line, 4096, file);
        dir->people[i] = malloc(256);
        strcpy(dir->people[i], line);

        fgets(skip, 4096, file); // skip useless line
    }
    
    return dir;
}

struct dir **read_input(int *num){

    char filename[] = "pplinp.txt";
    FILE *file = fopen(filename, "r");
    char line[4096];

    // skip user search
    fgets(line, 4096, file);

    // get num dirs
    fgets(line, 4096, file);
    line[ strlen(line) - 1 ] = '\0';
    int num_dirs = atoi(line);

    struct dir **dirs = malloc( sizeof( struct dir *) * num_dirs );
    for(int i = 0; i < num_dirs; i++){ dirs[i] = read_dir(file, dirs[i]); } // init dirs

    *num = num_dirs;

    fclose(file);

    return dirs;

}

int **matches(char *query, struct dir **dirs, int num_dirs, int *num_found){

    int **matches = malloc( sizeof(int*) * MAXPEOPLE );
    int matches_found = 0;

    for(int i = 0; i < num_dirs; i++){

        for(int j = 0; j < dirs[i]->num_ppl; j++){
            // if query matches person, add to matches
            if( is_similar( query, dirs[i]->people[j] ) ){
                matches[matches_found] = malloc(sizeof(int) * 2);
                matches[matches_found][0] = i;
                matches[matches_found][1] = j;
                matches_found++;
            }
        }

    }

    *num_found = matches_found;
    return matches;

}

void writeMatches(int **matches, int num_matches){

    char filename[] = "pplout.txt";
    FILE *file = fopen(filename, "w");

    fprintf(file, "%d\n", num_matches);

    for(int i = 0; i < num_matches; i++){

        fprintf(file, "%d %d\n", matches[i][0], matches[i][1]);

    }
    fclose(file);

}