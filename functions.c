#include "functions.h"

// note i didnt care about readability of my code AT ALL :)

int max(int num_1, int num_2){ if(num_1 < num_2){ return num_2; } return num_1; } // return max val

// if youre reading this steven, i wouldnt even waste time trying to understand this function
int LCShelper(char str_1[], char str_2[], struct map *map){

    char *key = make_key( str_1, str_2 );

    int val = in_map( map, key );
    if( val != -1 ){ return val; } // already did the computation, dont do it again!!!! #dynamicprogramming >:)

    /* if either string "", the longest common substring
    will be 0 */
    if( !strlen(str_1) || !strlen(str_2) ){ return 0; }

    else{
        // we know val isnt in map so lets to the calculations and add it
        if( str_1[0] == str_2[0] ){
            
            // chars match
            struct hash_node *node = init_node( key, 1 + LCShelper( str_1 + 1, str_2 + 1, map ) );
            add_to_map( map, node );

        }
        else{
            
            // chars dont match
            struct hash_node *node = init_node( key, max( LCShelper( str_1 + 1, str_2, map ), LCShelper( str_1, str_2 + 1, map ) ) );
            add_to_map( map, node );

        }

    }

    return in_map(map, key); // return val for cur key

}

// do init stuff, call LCS helper
int LCS(char str_1[], char str_2[]){

    struct map *map = init_map();
    return LCShelper(str_1, str_2, map);

}

// make stuff lowercase
void lower(char str[]){

    for(int i = 0; i < strlen(str); i++){ str[i] = tolower(str[i]); }
    
}

// check if str1 is exact substr of str2
int is_exact_substr(char str1[], char str2[]){

    if( strlen(str2) == 0 ){ return 0; } // str2 empty, false

    int len = strlen(str1);
    int i;
    for(i = 0; i < len && i < strlen(str2); i++){ if( str1[i] != str2[i] ){ return 0; } } // char not equal, 0

    if( i == len ){ return 1; } // i == len of str 1, 1

    return 0; // else, 0

}

// separate a str into a first and last name
char *separate(char str[], int first){

    if(!strlen(str)){ return ""; } // if str empty, ret empty str

    char *tok = strtok(str, " ");

    if(first){ return tok; } // first name
    return str + strlen(tok) + 1; // last name

}

// return similarity between strings using LCS. divide by larger string length
float similarity(char str_1[], char str_2[]){ 
    return (float) LCS(str_1, str_2 ) / (float) (strlen(str_1) > strlen(str_2) ? strlen(str_1) : strlen(str_2)); 
}

// combine checking methods to check if strs are similar
int is_similar(char str1[], char str2[]){

    lower(str1); lower(str2); // make strs lowercase

    // separate first and last
    char *first = separate(str2, 1);
    char *last = separate(str2, 0);

    // return similar if user str is exact sub str of first or last name
    if( is_exact_substr(str1, first) || is_exact_substr(str1, last)){ return 1; }

    // if similarity > SIMILARITY_SENSITIVITY, return true
    float sim = similarity(str1, str2);
    if( sim > SIMILARITY_SENSITIVITY ){ return 1; }

    return 0;

}