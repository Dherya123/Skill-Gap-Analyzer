#ifndef JOB_LIST_H
#define JOB_LIST_H

#include "skill_set.h"

typedef struct skillNode {
    char skill[50];
    struct skillNode* next;
} SkillNode;

typedef struct job {
    char jobName[50];
    SkillNode* skillList;
    struct job* next;
} Job;

Job* createJob(char* name) {
    Job* j = malloc(sizeof(Job));
    strcpy(j->jobName, name);
    j->skillList = NULL;
    j->next = NULL;
    return j;
}

// Add skill to job
void addSkill(Job* job, char* skill) {
    SkillNode* newNode = (SkillNode*)malloc(sizeof(SkillNode));
    strcpy(newNode->skill, skill);
    toLowerCase(newNode->skill);
    newNode->next = job->skillList;
    job->skillList = newNode;
}

Job* insertJob(Job* head, Job* newJob) {
    if(head==NULL) return newJob;

    Job* temp = head;
    while(temp->next) temp = temp->next;
    temp->next = newJob;
    return head;
}

// Initialize jobs
Job* initializeJobs() {
    Job* head = NULL;
    Job* j;

    j = createJob("Software Engineer");
    addSkill(j, "C");
    addSkill(j, "DSA");
    addSkill(j, "DBMS");
    addSkill(j, "OS");
    head = insertJob(head,j);

    j = createJob("Game Developer");
    addSkill(j, "C++");
    addSkill(j, "DSA");
    addSkill(j, "Math");
    addSkill(j, "Graphics");
    head = insertJob(head,j);

    j = createJob("Web Developer");
    addSkill(j, "HTML");
    addSkill(j, "CSS");
    addSkill(j, "JavaScript");
    addSkill(j, "React");
    head = insertJob(head,j);

    j = createJob("Data Analyst");
    addSkill(j, "Python");
    addSkill(j, "SQL");
    addSkill(j, "Statistics");
    addSkill(j, "Excel");
    head = insertJob(head,j);

    return head;
}

// 🔥 UPDATED ANALYSIS FUNCTION
float analyzeJob(Job* job, char allMissing[][50], int* totalMissing) {
    int matched = 0, total = 0;

    char missing[20][50];
    int missCount = 0;

    printf("\nJob Role: %s\n", job->jobName);

    printf("Matched Skills:\n");

    SkillNode* temp = job->skillList;

    while(temp) {
        total++;

        if(search(temp->skill)) {
            printf("✔ %s\n", temp->skill);
            matched++;
        } else {
            strcpy(missing[missCount++], temp->skill);

            // 🔥 Add to global list (avoid duplicates)
            int found = 0;
            for(int i = 0; i < *totalMissing; i++) {
                if(strcmp(allMissing[i], temp->skill) == 0) {
                    found = 1;
                    break;
                }
            }

            if(!found) {
                strcpy(allMissing[*totalMissing], temp->skill);
                (*totalMissing)++;
            }
        }
        temp = temp->next;
    }

    printf("Missing Skills:\n");

    if(missCount == 0) {
        printf("None\n");
    } else {
        for(int i = 0; i < missCount; i++) {
            printf("✘ %s\n", missing[i]);
        }
    }

    float percent = ((float)matched / total) * 100;

    printf("Match Percentage: %.2f%%\n", percent);
    printf("----------------------------\n");

    return percent;
}

#endif