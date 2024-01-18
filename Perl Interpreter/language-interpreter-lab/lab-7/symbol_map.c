#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol_map.h"

// Function to create a new symbol map
struct SymbolMap *createSymbolMap(struct SymbolMap *map) {
    map = (struct SymbolMap *)malloc(sizeof(struct SymbolMap));
    if (map == NULL) {
        // Handle memory allocation failure
        exit(EXIT_FAILURE);
    }
    map->head = NULL;
    return map;
}

// Function to insert a symbol into the map
void insertSymbol(struct SymbolMap *map, const char *key, struct expr *value) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        // Handle memory allocation failure
        exit(EXIT_FAILURE);
    }
    newNode->key = key;
    newNode->value = value;
    newNode->next = map->head;
    map->head = newNode;
}

// Function to get a symbol from the map
struct expr *getSymbol(struct SymbolMap *map, const char *key) {
    struct Node *current = map->head;
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }
    return NULL; // Key not found
}

// Function to delete a symbol from the map
void deleteSymbol(struct SymbolMap *map, const char *key) {
    struct Node *current = map->head;
    struct Node *prev = NULL;

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            if (prev == NULL) {
                map->head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

// Function to destroy the symbol map and free memory
void destroySymbolMap(struct SymbolMap *map) {
    struct Node *current = map->head;
    struct Node *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    free(map);
}
