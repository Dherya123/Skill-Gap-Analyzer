#ifndef JOB_LIST_H
#define JOB_LIST_H

#include "skill_set.h"

typedef struct skillNode 
{
    char skill[50];
    struct skillNode* next;
} SkillNode;

typedef struct job 
{
    char jobName[50];
    SkillNode* skillList;
} Job;

// Add skill to job
void addSkill(Job* job, char* skill) 
{
    SkillNode* newNode = (SkillNode*)malloc(sizeof(SkillNode));
    strcpy(newNode->skill, skill);
    toLowerCase(newNode->skill);
    newNode->next = job->skillList;
    job->skillList = newNode;
}

// Initialize jobs
void initializeJobs(Job jobs[], int* count) 
{
    *count = 4;

    strcpy(jobs[0].jobName, "Software Engineer");
    jobs[0].skillList = NULL;
    addSkill(&jobs[0], "C");
    addSkill(&jobs[0], "DSA");
    addSkill(&jobs[0], "DBMS");
    addSkill(&jobs[0], "OS");

    strcpy(jobs[1].jobName, "Game Developer");
    jobs[1].skillList = NULL;
    addSkill(&jobs[1], "C++");
    addSkill(&jobs[1], "DSA");
    addSkill(&jobs[1], "Math");
    addSkill(&jobs[1], "Graphics");

    strcpy(jobs[2].jobName, "Web Developer");
    jobs[2].skillList = NULL;
    addSkill(&jobs[2], "HTML");
    addSkill(&jobs[2], "CSS");
    addSkill(&jobs[2], "JavaScript");
    addSkill(&jobs[2], "React");

    strcpy(jobs[3].jobName, "Data Analyst");
    jobs[3].skillList = NULL;
    addSkill(&jobs[3], "Python");
    addSkill(&jobs[3], "SQL");
    addSkill(&jobs[3], "Statistics");
    addSkill(&jobs[3], "Excel");
}

// 🔥 UPDATED ANALYSIS FUNCTION
float analyzeJob(Job job, char allMissing[][50], int* totalMissing) 
{
    int matched = 0, total = 0;

    char missing[20][50];
    int missCount = 0;

    printf("\nJob Role: %s\n", job.jobName);

    printf("Matched Skills:\n");

    SkillNode* temp = job.skillList;

    while(temp) 
    {
        total++;

        if(search(temp->skill)) 
        {
            printf("✔ %s\n", temp->skill);
            matched++;
        } else 
        {
            strcpy(missing[missCount++], temp->skill);

            // 🔥 Add to global list (avoid duplicates)
            int found = 0;
            for(int i = 0; i < *totalMissing; i++) 
            {
                if(strcmp(allMissing[i], temp->skill) == 0) 
                {
                    found = 1;
                    break;
                }
            }

            if(!found) 
            {
                strcpy(allMissing[*totalMissing], temp->skill);
                (*totalMissing)++;
            }
        }
        temp = temp->next;
    }

    printf("Missing Skills:\n");

    if(missCount == 0) 
    {
        printf("None\n");
    } else 
    {
        for(int i = 0; i < missCount; i++) 
        {
            printf("✘ %s\n", missing[i]);
        }
    }

    float percent = ((float)matched / total) * 100;

    printf("Match Percentage: %.2f%%\n", percent);
    printf("----------------------------\n");

    return percent;
}

#endif