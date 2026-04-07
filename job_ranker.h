#ifndef JOB_RANKER_H
#define JOB_RANKER_H

#include <string.h>

#define MAX_JOBS 10

typedef struct 
{
    char jobName[50];
    float matchPercent;
} Result;

typedef struct 
{
    Result arr[MAX_JOBS];
    int size;
} MaxHeap;

void swap(Result* a, Result* b) 
{
    Result t = *a; *a = *b; *b = t;
}

void heapifyUp(MaxHeap* h, int i) 
{
    while(i > 0) 
    {
        int p = (i - 1) / 2;
        if(h->arr[p].matchPercent < h->arr[i].matchPercent) 
        {
            swap(&h->arr[p], &h->arr[i]);
            i = p;
        } else break;
    }
}

void heapifyDown(MaxHeap* h, int i) 
{
    int largest = i;
    int l = 2*i + 1, r = 2*i + 2;

    if(l < h->size && h->arr[l].matchPercent > h->arr[largest].matchPercent)
    {
        largest = l;
    }
        
    if(r < h->size && h->arr[r].matchPercent > h->arr[largest].matchPercent)
    {
        largest = r;
    }

    if(largest != i) 
    {
        swap(&h->arr[i], &h->arr[largest]);
        heapifyDown(h, largest);
    }
}

void insertHeap(MaxHeap* h, Result r) 
{
    h->arr[h->size] = r;
    heapifyUp(h, h->size);
    h->size++;
}

Result extractMax(MaxHeap* h) 
{
    Result r = h->arr[0];
    h->arr[0] = h->arr[--h->size];
    heapifyDown(h, 0);
    return r;
}

#endif