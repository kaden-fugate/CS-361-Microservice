#ifndef HASH_H
#define HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAP_SIZE 512
#define KEY_SIZE 2048

struct hash_node{

    char *key; // to save time, we will use str key rather than void*
    int value; // same for val but int instead
    struct hash_node *next;

};

struct map{

    struct hash_node **node_arr;

};

struct hash_node *init_node(char*, int);

struct map *init_map();
int in_map(struct map *, char *);
void add_to_map(struct map *, struct hash_node *);
int hash_key(char*);
char *make_key(char*, char*);

#endif