#include <unistd.h>

#include "dir.h"
#include "functions.h"
#include "hash.h"

void clearFiles(){ FILE * file = fopen("pplinp.txt", "w"); fclose(file); file = fopen("pplout.txt", "w"); fclose(file); }

int fileEmpty(){

    FILE *file= fopen("pplinp.txt", "r");

    fseek(file, 0, SEEK_END);
    int fileSize = ftell(file);

    // Close the file
    fclose(file);

    return fileSize == 0 ? 1 : 0;

}

int main(){

    while( fileEmpty() ){  }
    sleep(0.1);

    char *query = get_query();
    int num_dirs = 0;
    struct dir **dirs = read_input(&num_dirs);
    int num_found = 0;
    int **found = matches(query, dirs, num_dirs, &num_found);

    writeMatches(found, num_found);

    sleep(5);
    clearFiles();

    return 0;

}