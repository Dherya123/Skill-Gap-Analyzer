// Topic - Skill-Gap Analyser

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SKILLS 20
#define MAX_JOBS 5

// function to convert into lover case
void toLowerCase(char str[])
{
    for(int i=0; str[i]; i++)
    {
        if(str[i] >= 'A' && str[i] <= 'Z')
            str[i] = str[i] + 32;
    }
}

// Defining BST Node Structure for organising student skills
typedef struct node
{
    char skill[50];
    struct node* left;
    struct node* right;
} BSTNode;

// structure for Job (ADT)
typedef struct job 
{
    char jobName[50];
    char skills[MAX_SKILLS][50];
    int skillCount;
} Job;

// Structure for Storing Result 
typedef struct result
{   
    char jobName[50];
    float matchPercent;
} Result;

// BST function for creating skill Node
BSTNode* createNode(char skill[])
{
    BSTNode* newNode = (BSTNode*)malloc(sizeof(BSTNode)); // Allocating memory to the skill Node from heap
    strncpy(newNode->skill, skill, sizeof(newNode->skill)-1); // strncpy is used to prevent from buffer overflow
    newNode->skill[sizeof(newNode->skill)-1] = '\0';
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

// BST function for inserting Skill on existing skill tree
BSTNode* insertSkill(BSTNode* root, char skill[])
{
    if(root == NULL)
    {
        return createNode(skill);
    }

    if(strcmp(root->skill, skill) > 0)
    {
        root->left = insertSkill(root->left, skill);
    }
    else if(strcmp(root->skill, skill) < 0)
    {
        root->right = insertSkill(root->right, skill);
    }

    return root;
}

// BST function for searching skills
int searchSkill(BSTNode* root, char skill[])
{
    if(root == NULL)
    {
        return 0;
    }

    if(strcmp(root->skill, skill) == 0)
    {
        return 1;
    }
    if(strcmp(root->skill, skill) > 0)
    {
        return searchSkill(root->left, skill);
    }

    return searchSkill(root->right, skill);
}

// Input function for student skills
BSTNode* inputStudentSkills(BSTNode* root)
{
    int n;
    char skill[50];

    printf("Enter the no of Skills you have : ");
    scanf("%d", &n);
    getchar(); // for leftover newline

    printf("Enter the Skills you have : \n");

    for(int i = 0; i < n; i++)
    {
        fgets(skill, sizeof(skill), stdin);
        skill[strcspn(skill, "\n")] = 0;
        toLowerCase(skill);
        root = insertSkill(root, skill);
    }

    return root;
}

// Job initialization function
void initializeJob(Job job[], int *jobCount)
{
    *jobCount = 4;

    strcpy(job[0].jobName,"Software Engineer");

    strcpy(job[0].skills[0],"C");
    toLowerCase(job[0].skills[0]);

    strcpy(job[0].skills[1],"DSA");
    toLowerCase(job[0].skills[1]);

    strcpy(job[0].skills[2],"DBMS");
    toLowerCase(job[0].skills[2]);

    strcpy(job[0].skills[3],"OS");
    toLowerCase(job[0].skills[3]);

    job[0].skillCount=4;


    strcpy(job[1].jobName,"Game Developer");

    strcpy(job[1].skills[0],"C++");
    toLowerCase(job[1].skills[0]);

    strcpy(job[1].skills[1],"DSA");
    toLowerCase(job[1].skills[1]);

    strcpy(job[1].skills[2],"Math");
    toLowerCase(job[1].skills[2]);

    strcpy(job[1].skills[3],"Graphics");
    toLowerCase(job[1].skills[3]);

    job[1].skillCount=4;


    strcpy(job[2].jobName,"Web Developer");

    strcpy(job[2].skills[0],"HTML");
    toLowerCase(job[2].skills[0]);

    strcpy(job[2].skills[1],"CSS");
    toLowerCase(job[2].skills[1]);

    strcpy(job[2].skills[2],"JavaScript");
    toLowerCase(job[2].skills[2]);

    strcpy(job[2].skills[3],"React");
    toLowerCase(job[2].skills[3]);

    job[2].skillCount=4;


    strcpy(job[3].jobName,"Data Analyst");

    strcpy(job[3].skills[0],"Python");
    toLowerCase(job[3].skills[0]);

    strcpy(job[3].skills[1],"SQL");
    toLowerCase(job[3].skills[1]);

    strcpy(job[3].skills[2],"Statistics");
    toLowerCase(job[3].skills[2]);

    strcpy(job[3].skills[3],"Excel");
    toLowerCase(job[3].skills[3]);

    job[3].skillCount=4;
}   

// Sorting Missing Skills
void sortMissingSkills(char skill[][50], int n)
{
    char temp[50];
    
    for(int i = 0; i < n - 1; i++)
    {
        for(int j = 0; j < n - i - 1; j++)
        { 
            if(strcmp(skill[j], skill[j+1]) > 0)
            {
                strcpy(temp, skill[j]);
                strcpy(skill[j], skill[j+1]);
                strcpy(skill[j+1], temp);
            }
        }
    }
}

// function for Calculating percentage of matched skills
float calculatePercentage(int matched, int total)
{
    return ((float)matched/total)*100;
}

// function for Analysing job
float analyzeJob(BSTNode* root, Job job)
{
    int matched = 0;
    char missingSkills[MAX_SKILLS][50];

    int missingCount = 0;

    printf("\nJob Role : %s\n", job.jobName);
    printf("\nMatched Skills :\n");

    for(int i = 0; i < job.skillCount; i++)
    {
        if(searchSkill(root, job.skills[i]))
        {
            printf("%s\n", job.skills[i]);
            matched++;
        }
        else
        {
            strcpy(missingSkills[missingCount], job.skills[i]);
            missingCount++;
        }
    }

    printf("\nMissing Skills :\n");
    if(missingCount == 0)
    {
        printf("None\n");
    }
    else
    {
        sortMissingSkills(missingSkills, missingCount);

        for(int i = 0; i < missingCount; i++)
        {
            printf("%s\n", missingSkills[i]);
        }
    }

    float percent = calculatePercentage(matched, job.skillCount);

    printf("\nMatch Percentage: %.2f%%\n",percent);

    printf("\n----------------------------\n");

    return percent;
}


// function for finding best job
void findBestJob(Result result[], int jobCount)
{
    float max = result[0].matchPercent;

    int index = 0;

    for(int i = 1; i < jobCount; i++)
    {
        if(result[i].matchPercent > max)
        {
            max = result[i].matchPercent;
            index = i;
        }
    }

    printf("\nBest Matching Job : %s\n", result[index].jobName);
}

int main()
{
    BSTNode* root = NULL;
    Job jobs[MAX_JOBS];
    Result results[MAX_JOBS];

    int jobCount;

    printf("\n======= SKILL GAP ANALYSIS =======\n");

    initializeJob(jobs, &jobCount);
    root = inputStudentSkills(root);

    for(int i = 0; i < jobCount; i++)
    {
        float percent = analyzeJob(root, jobs[i]);
        strcpy(results[i].jobName, jobs[i].jobName);
        results[i].matchPercent = percent;
    }

    findBestJob(results, jobCount);
    printf("\n==================================\n");

    return 0;
}