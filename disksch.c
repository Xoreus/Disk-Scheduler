
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <limits.h>
FILE *INPUT;
FILE *OUTPUT;
#define numofdisks (25)
int diskpos[numofdisks];
int initialheadpos;
int mindisk = 0;
int maxdisk = 99;

void FCFS();
void SCAN();
void CSCAN();
int compare(const void *first, const void *second);

int main(int argc, char *argv[])
{
    if (argv[1])
    {
        initialheadpos = atoi(argv[1]);
    }
    else
    {
        initialheadpos = 33;
    }
    INPUT = fopen("input.txt", "r");
    if (INPUT == NULL)
    {
        printf("ERROR -> MISSING input.txt");
        return 0;
    }
    OUTPUT = fopen("output.txt", "w+");
    char buff[10];
    int i = 0;
    while (fgets(buff, sizeof(buff), INPUT) != NULL)
    {
        diskpos[i] = atoi(buff);
        //fprintf(OUTPUT, "%d\n",diskpos[i]);
        i++;
    }
    FCFS();
    fprintf(OUTPUT, "\n");
    SCAN();
    fprintf(OUTPUT, "\n");
    CSCAN();
    fclose(OUTPUT);
    fclose(INPUT);
    return 0;
}

void FCFS()
{
    int current_pos = initialheadpos;
    int totalmoves = 0;
    fprintf(OUTPUT, "\n");
    fprintf(OUTPUT, "FCFS Algorithm\nInitial head position = %d\nSeek Sequence is:\n", current_pos);
    for (int i = 0; i < numofdisks; i++)
    {
        totalmoves = abs(current_pos - diskpos[i]) + totalmoves;
        current_pos = diskpos[i];
        fprintf(OUTPUT, "%d\n", current_pos);
    }
    fprintf(OUTPUT, "Total head movement for FCFS = %d", totalmoves);
    return;
}

void SCAN()
{
    int current_pos = initialheadpos;
    int totalmoves = 0;
    int sorted_diskpos[numofdisks];
    fprintf(OUTPUT, "\n");
    fprintf(OUTPUT, "SCAN Algorithm\nInitial head position = %d\nSeek Sequence is:\n", current_pos);
    for (int i = 0; i < numofdisks; i++)
    {
        sorted_diskpos[i] = diskpos[i];
    }
    qsort(sorted_diskpos, numofdisks, sizeof(int), compare);
    //for (int i=0;i<numofdisks;i++) {
    //    printf("%d\n",sorted_diskpos[i]);
    //}
    int less = 0;
    int greater = numofdisks;
    for (int i = 0; i < numofdisks; i++)
    {
        if (sorted_diskpos[i] <= current_pos)
        {
            less = i;
        }
        if (sorted_diskpos[(numofdisks-1) - i] > current_pos)
        {
            greater = (numofdisks-1) - i;
            //printf("%d\n", greater);
        }
    }
    //printf("less:%d\n greater:%d\n",less, greater);
    if (less != greater)
    {
        for (int i = less; i >= 0; i--)
        {
            totalmoves = abs(current_pos - sorted_diskpos[i]) + totalmoves;
            //printf("%d\n",abs(current_pos - sorted_diskpos[i]));
            current_pos = sorted_diskpos[i];
            fprintf(OUTPUT, "%d\n", current_pos);
        }
        if (sorted_diskpos[(numofdisks-1)] > initialheadpos)
        {
            totalmoves = abs(current_pos - mindisk) + totalmoves;
            current_pos = mindisk;
            //printf("CURRENT POS:%d\n",current_pos);
        }
        for (int i = greater; i < numofdisks; i++)
        {
            totalmoves = abs(current_pos - sorted_diskpos[i]) + totalmoves;
            //printf("%d\n",abs(current_pos - sorted_diskpos[i]));
            current_pos = sorted_diskpos[i];
            fprintf(OUTPUT, "%d\n", current_pos);
        }
    }
    else if (less == greater && sorted_diskpos[less] > current_pos)
    {
        totalmoves = abs(current_pos - mindisk) + totalmoves;
        current_pos = mindisk;
        for (int i = greater; i < numofdisks; i++)
        {
            totalmoves = abs(current_pos - sorted_diskpos[i]) + totalmoves;
            //printf("%d\n",abs(current_pos - sorted_diskpos[i]));
            current_pos = sorted_diskpos[i];
            fprintf(OUTPUT, "%d\n", current_pos);
        }
    }
    else if (less == greater && sorted_diskpos[less] <= current_pos)
    {
        for (int i = less; i >= 0; i--)
        {
            totalmoves = abs(current_pos - sorted_diskpos[i]) + totalmoves;
            //printf("%d\n",abs(current_pos - sorted_diskpos[i]));
            current_pos = sorted_diskpos[i];
            fprintf(OUTPUT, "%d\n", current_pos);
        }
    }
    fprintf(OUTPUT, "Total head movement for SCAN = %d", totalmoves);
    return;
}

void CSCAN()
{
    int current_pos = initialheadpos;
    int totalmoves = 0;
    int sorted_diskpos[numofdisks];
    fprintf(OUTPUT, "\n");
    fprintf(OUTPUT, "C_SCAN Algorithm\nInitial head position = %d\nSeek Sequence is:\n", current_pos);
    for (int i = 0; i < numofdisks; i++)
    {
        sorted_diskpos[i] = diskpos[i];
    }
    qsort(sorted_diskpos, numofdisks, sizeof(int), compare);
    //for (int i=0;i<numofdisks;i++) {
    //    printf("%d\n",sorted_diskpos[i]);
    //}
    int less = 0;
    int greater = numofdisks;
    for (int i = 0; i < numofdisks; i++)
    {
        if (sorted_diskpos[i] < current_pos)
        {
            less = i;
        }
        if (sorted_diskpos[(numofdisks-1) - i] >= current_pos)
        {
            greater = (numofdisks-1) - i;
            //printf("%d\n", greater);
        }
    }
    //printf("less:%d\n greater:%d\n",less, greater);
    if (less != greater)
    {
        for (int i = greater; i < numofdisks; i++)
        {
            totalmoves = abs(current_pos - sorted_diskpos[i]) + totalmoves;
            //printf("%d\n",abs(current_pos - sorted_diskpos[i]));
            //printf("CHECK: %d\n",sorted_diskpos[i]);
            current_pos = sorted_diskpos[i];
            fprintf(OUTPUT, "%d\n", current_pos);
        }
        if (sorted_diskpos[0] < initialheadpos)
        {
            totalmoves = abs(current_pos - maxdisk) + totalmoves;
            //printf("Front: %d\n",abs(current_pos - maxdisk));
            current_pos = maxdisk;
            totalmoves = abs(current_pos - mindisk) + totalmoves;
            //printf("Back: %d\n",abs(current_pos - mindisk));
            current_pos = mindisk;
        }
        for (int i = 0; i <= less; i++)
        {
            totalmoves = abs(current_pos - sorted_diskpos[i]) + totalmoves;
            //printf("%d\n",abs(current_pos - sorted_diskpos[i]));
            current_pos = sorted_diskpos[i];
            fprintf(OUTPUT, "%d\n", current_pos);
        }
    }
    else if (less == greater && sorted_diskpos[greater] >= current_pos)
    {   //printf("check");
        for (int i = greater; i < numofdisks; i++)
        {
            totalmoves = abs(current_pos - sorted_diskpos[i]) + totalmoves;
            //printf("%d\n",abs(current_pos - sorted_diskpos[i]));
            current_pos = sorted_diskpos[i];
            fprintf(OUTPUT, "%d\n", current_pos);
        }
    }
    else if (less == greater && sorted_diskpos[less] < current_pos)
    {
        totalmoves = abs(current_pos - maxdisk) + totalmoves;
        current_pos = maxdisk;
        totalmoves = abs(current_pos - mindisk) + totalmoves;
        current_pos = mindisk;
        for (int i = greater; i < numofdisks; i++)
        {
            totalmoves = abs(current_pos - sorted_diskpos[i]) + totalmoves;
            //printf("%d\n",abs(current_pos - sorted_diskpos[i]));
            current_pos = sorted_diskpos[i];
            fprintf(OUTPUT, "%d\n", current_pos);
        }
    }
    fprintf(OUTPUT, "Total head movement for C_SCAN = %d", totalmoves);
    return;
}

int compare(const void *first, const void *second)
{
    return (*(int *)first - *(int *)second);
}
