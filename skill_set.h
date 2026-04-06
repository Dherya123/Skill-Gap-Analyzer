#ifndef HASH_H
#define HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_SIZE 11
#define LOAD_FACTOR 0.7

typedef struct node {
    char skill[50];
    struct node* next;
} Node;

Node** hashTable;
int tableSize = INITIAL_SIZE;
int elementCount = 0;

void toLowerCase(char str[]) {
    for(int i = 0; str[i]; i++)
        if(str[i] >= 'A' && str[i] <= 'Z')
            str[i] += 32;
}

unsigned long hashFunction(char str[]) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return hash % tableSize;
}

Node** createHashTable(int size) {
    Node** table = (Node**)malloc(size * sizeof(Node*));
    for(int i = 0; i < size; i++) table[i] = NULL;
    return table;
}

void insert(char* skill);

void rehash() {
    Node** oldTable = hashTable;
    int oldSize = tableSize;

    tableSize = 2 * oldSize + 1;
    hashTable = createHashTable(tableSize);
    elementCount = 0;

    for(int i = 0; i < oldSize; i++) {
        Node* temp = oldTable[i];
        while(temp) {
            insert(temp->skill);
            temp = temp->next;
        }
    }
    free(oldTable);
}

void insert(char* skill) {
    float load = (float)elementCount / tableSize;
    if(load > LOAD_FACTOR) rehash();

    int index = hashFunction(skill);

    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->skill, skill);
    newNode->next = hashTable[index];
    hashTable[index] = newNode;

    elementCount++;
}

int search(char* skill) {
    int index = hashFunction(skill);
    Node* temp = hashTable[index];

    while(temp) {
        if(strcmp(temp->skill, skill) == 0)
            return 1;
        temp = temp->next;
    }
    return 0;
}

#endif