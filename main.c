#include <stdio.h>
#include "skill_set.h"
#include "job_list.h"
#include "job_ranker.h"
#include "inverted_index.h"
#include "learning_path.h"

int main() 
{
    Job jobs[10];
    int jobCount;

    hashTable = createHashTable(tableSize);
    indexTable = createIndexTable(tableSize);

    initializeJobs(jobs, &jobCount);
    buildIndex(jobs, jobCount);

    int n;
    char skill[50];
    char allMissing[100][50];
    int totalMissing = 0;

    printf("Enter number of skills: ");
    scanf("%d", &n);
    getchar();

    printf("Enter the Skills you have: \n");

    for(int i = 0; i < n; i++) 
    {
        fgets(skill, sizeof(skill), stdin);
        skill[strcspn(skill, "\n")] = 0;
        toLowerCase(skill);
        insert(skill);
    }

    MaxHeap heap = {.size = 0};

    for(int i = 0; i < jobCount; i++) 
    {
        Result r;
        strcpy(r.jobName, jobs[i].jobName);
        r.matchPercent = analyzeJob(jobs[i], allMissing, &totalMissing);
        insertHeap(&heap, r);
    }

    printf("\n=== Job Ranking ===\n");
    while(heap.size > 0) {
        Result r = extractMax(&heap);
        printf("%s → %.2f%%\n", r.jobName, r.matchPercent);
    }

    generateLearningPath(allMissing, totalMissing);

    while(1) 
    {
        printf("\nSearch skill (press q to quit): ");

        fgets(skill, sizeof(skill), stdin);
        skill[strcspn(skill, "\n")] = 0;

        // convert to lowercase
        toLowerCase(skill);

        // 🔴 Exit condition
        if(strcmp(skill, "q") == 0) 
        {
            printf("Exiting program...\n");
            break;
        }

        // 🔍 Perform search
        searchBySkill(skill);
    }

    return 0;
}