#ifndef LEARNING_PATH_H
#define LEARNING_PATH_H

#include <stdio.h>
#include <string.h>

// ================= STRUCTURES =================

typedef struct {
    char skill[50];
    int priority;
} SkillPriority;

typedef struct {
    SkillPriority arr[50];
    int size;
} SkillHeap;

// ================= PRIORITY LOGIC =================

int getPriority(char skill[]) {

    // Core skills → highest priority
    if(strcmp(skill, "dsa") == 0 || strcmp(skill, "c") == 0 || strcmp(skill, "python") == 0)
        return 3;

    // Important skills → medium priority
    if(strcmp(skill, "dbms") == 0 || strcmp(skill, "os") == 0 || strcmp(skill, "sql") == 0)
        return 2;

    // Other skills → low priority
    return 1;
}

// ================= HEAP FUNCTIONS =================

void swapSkill(SkillPriority* a, SkillPriority* b) {
    SkillPriority t = *a;
    *a = *b;
    *b = t;
}

void heapifyUpSkill(SkillHeap* h, int i) {
    while(i > 0) {
        int p = (i - 1) / 2;

        if(h->arr[p].priority < h->arr[i].priority) {
            swapSkill(&h->arr[p], &h->arr[i]);
            i = p;
        } else break;
    }
}

void heapifyDownSkill(SkillHeap* h, int i) {
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if(l < h->size && h->arr[l].priority > h->arr[largest].priority)
        largest = l;

    if(r < h->size && h->arr[r].priority > h->arr[largest].priority)
        largest = r;

    if(largest != i) {
        swapSkill(&h->arr[i], &h->arr[largest]);
        heapifyDownSkill(h, largest);
    }
}

// ================= INSERT =================

void insertSkillHeap(SkillHeap* h, char skill[]) {
    SkillPriority s;

    strcpy(s.skill, skill);
    s.priority = getPriority(skill);

    h->arr[h->size] = s;
    heapifyUpSkill(h, h->size);
    h->size++;
}

// ================= EXTRACT =================

SkillPriority extractMaxSkill(SkillHeap* h) {
    SkillPriority s = h->arr[0];

    h->arr[0] = h->arr[--h->size];
    heapifyDownSkill(h, 0);

    return s;
}

// ================= LEARNING PATH =================

void generateLearningPath(char missing[][50], int n) {

    // 🔴 Base case
    if(n == 0) {
        printf("\nNo learning required. You are fully matched!\n");
        return;
    }

    SkillHeap h;
    h.size = 0;

    // Insert missing skills
    for(int i = 0; i < n; i++) {
        insertSkillHeap(&h, missing[i]);
    }

    printf("\n🔥 Recommended Learning Path:\n");

    int step = 1;

    while(h.size > 0) {
        SkillPriority s = extractMaxSkill(&h);
        printf("Step %d: Learn %s\n", step++, s.skill);
    }
}

#endif