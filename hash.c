#include "hash.h"

// Note: for this implementation of a hash table, we will not need to
// implement a remove from map function

struct hash_node *init_node(char *key, int value){

    struct hash_node *node = malloc( sizeof( struct hash_node ) );
    node->key = key;
    node->value = value;
    node->next = NULL;

    return node;

}

struct map *init_map(){

    struct map *map = malloc( sizeof( struct map ) ); // alloc map
    map->node_arr = malloc( MAP_SIZE * sizeof( struct hash_node * ) ); // alloc node arr

    for(int i = 0; i < MAP_SIZE; i++){ map->node_arr[i] = NULL; }

    return map;

}

int hash_key(char *key){

    int hash = 37;

    for( int i = 0; i < strlen( key ); i++ ){

        hash += ( ( int ) key[i] ) * 11 ;

    }

    return hash % 512;

}

void insert(struct map *map, struct hash_node *node){

    int hash = hash_key(node->key);
    struct hash_node *temp = map->node_arr[hash];

    if( !temp ){ map->node_arr[hash] = node; return; }
    while( temp->next ){ temp = temp->next; }
    temp->next = node;

}

int in_map(struct map *map, char *key){

    int hash = hash_key(key);
    if(!map->node_arr[hash]){ return -1; } // list at hash is null, return 0

    // check list, return 1 if node->key = key
    struct hash_node *temp = map->node_arr[hash];
    while( temp ){ if( !strcmp(key, temp->key) ){ return temp->value; } temp = temp->next; }

    // not in list, return 0
    return -1;

}

void add_to_map(struct map *map, struct hash_node *node){

    if( in_map( map, node->key ) != -1 ){ return; }

    insert( map, node );

}

char *make_key(char *str_1, char *str_2){

    char *new_str = malloc(KEY_SIZE);
    sprintf(new_str, "%s%s", str_1, str_2);

    return new_str;

}

