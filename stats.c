/*
SYST44288
November 3, 2018
Students: Pavel K, Herit G
Professor: Christina R.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

int arrSize = 0;
int minv, maxv, avgv;

void *mathAverage(void *arg);
void *mathMin(void *arg);
void *mathMax(void *arg);
/*Calc min*/
void *mathMin(void *arg)
{

    minv = arr[0];
    int *arr = (int*)arg;
    int i;
    for(i=1; i<arrSize; i++)
    {
        if(minv > arr[i])
        minv = arr[i];
    }
    pthread_exit(0);
}
/*Calc max*/
void *mathMax(void *arg)
{
    maxv = arr[0];
    int *arr = (int*)arg;
    int i;  
    for(i=1; i<arrSize; i++)
    {
        if(maxv < arr[i])
        maxv = arr[i];
    }
    pthread_exit(0);
}
/*Calc average*/
void *mathAverage(void *arg)
{
    int sum = 0;
    int *arr = (int*)arg;
    int i;
    for(i=0; i<arrSize; i++)
    {
        sum += arr[i];
    }
    avgv = sum/arrSize;
    pthread_exit(0);
}

int main(int c, char *vals[])
{
    /*Store values in an array*/
    int arrArgs[c-1];
    for (int i=0; i<c-1; i++)
    {
        arrArgs[i] = atoi(vals[i+1]);
        arrSize++;
    }

    /*Define thread IDs*/
    pthread_t tidAvg = 110;
    pthread_t tidMin = 120;
    pthread_t tidMax = 130;
    /*Identify 3 separate threads*/
    pthread_create(&tidAvg,NULL,mathAverage,arrArgs);
    pthread_create(&tidMin,NULL,mathMin,arrArgs);
    pthread_create(&tidMax,NULL,mathMax,arrArgs);
    pthread_join(tidAvg,NULL);
    pthread_join(tidMin,NULL);
    pthread_join(tidMax,NULL);

    printf("The average value is %d\n", avgv);
    printf("The minimum value is %d\n", minv);
    printf("The maximum value is %d\n", maxv);
}
