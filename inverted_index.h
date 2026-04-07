#ifndef INDEX_H
#define INDEX_H

#include "job_list.h"

typedef struct jobNode {
    char jobName[50];
    struct jobNode* next;
} JobNode;

typedef struct indexNode {
    char skill[50];
    JobNode* jobList;
    struct indexNode* next;
} IndexNode;

IndexNode** indexTable;

IndexNode** createIndexTable(int size) {
    IndexNode** table = (IndexNode**)malloc(size * sizeof(IndexNode*));
    for(int i = 0; i < size; i++) table[i] = NULL;
    return table;
}

void addToIndex(char skill[], char jobName[]) {
    int index = hashFunction(skill);
    IndexNode* temp = indexTable[index];

    while(temp) {
        if(strcmp(temp->skill, skill) == 0) {
            JobNode* j = (JobNode*)malloc(sizeof(JobNode));
            strcpy(j->jobName, jobName);
            j->next = temp->jobList;
            temp->jobList = j;
            return;
        }
        temp = temp->next;
    }

    IndexNode* newIndex = (IndexNode*)malloc(sizeof(IndexNode));
    strcpy(newIndex->skill, skill);

    JobNode* j = (JobNode*)malloc(sizeof(JobNode));
    strcpy(j->jobName, jobName);
    j->next = NULL;

    newIndex->jobList = j;
    newIndex->next = indexTable[index];
    indexTable[index] = newIndex;
}

void buildIndex(Job* head) {
    for(int i = 0; i < 50; i++)
        indexTable[i] = NULL;

    Job* temp = head;

    while(temp) {
        SkillNode* s = temp->skillList;

        while(s) {
            addToIndex(s->skill, temp->jobName);
            s = s->next;
        }

        temp = temp->next;
    }
}

void searchBySkill(char skill[]) {
    int index = hashFunction(skill);

    // 🔴 Base Case 1: No index table
    if(indexTable == NULL) {
        printf("Index not initialized\n");
        return;
    }

    IndexNode* temp = indexTable[index];

    // 🔴 Base Case 2: No skill at this index
    if(temp == NULL) {
        printf("No jobs found for this skill\n");
        return;
    }

    // ✅ Iterative traversal
    while(temp != NULL) {

        if(strcmp(temp->skill, skill) == 0) {
            printf("\nJobs requiring '%s':\n", skill);

            JobNode* j = temp->jobList;

            // 🔴 Base Case 3: No jobs linked
            if(j == NULL) {
                printf("No jobs available\n");
                return;
            }

            while(j != NULL) {
                printf("%s\n", j->jobName);
                j = j->next;
            }
            return; // ✅ terminate once found
        }

        temp = temp->next;
    }

    // 🔴 Base Case 4: Skill not found after traversal
    printf("No jobs found for this skill\n");
}

#endif