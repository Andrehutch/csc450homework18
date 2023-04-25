#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define size 20
#define MaxThread 4
int * arr;
pthread_t threads [4];
int counter = 0;

void merge(int * arr, int low, int mid, int high){
    int * lower, * upper;
    lower = malloc(sizeof(int) * (mid - low +1));
    upper = malloc(sizeof(int) * (high - mid));
    int j, k;
    int n = low;
    for(int j = 0; j < (mid - low + 1); j++){
        lower[j] = arr[n];
        n++;
    }
    for(int k = 0; k < high - mid; k++){
        upper[k] = arr[n];
        n++;
    }
    n = low;
    j = 0;
    k = n;
    while(j < (mid -low + 1) && k < (high - mid)){
        if (lower[j] < upper[k]){
            arr[n] = lower[j];
            j++;
        } else {
            arr[n] = upper[k];
            k++;
        }
        n++;
    }
    while(j < mid - low + 1){
        arr[n] = lower[j];
        n++;
        j++;
    }
    while(k < high - mid){
        arr[n] = upper[k];
        n++;
        k++;
    }
    free(lower);
    free{upper};
}
void printArr(int * arr, int size){
    char * output;
    output = malloc(size * 4 + 1);
    for(int i = 0; i < size; i++){
        char strInt[3];
        sprintf(strInt, "%d", arr[i]);
        if (arr[i] > 9){
            output[i * 4] = strInt[0];
            output[i * 4 + 1] = strInt[1];
        }else {
            output[i * 4] = ' ';
            output[i * 4 + 1] = strInt[0];
        }
        output[i * 4 + 2] = ',';
        output[i * 4 + 3] = ' ';
    }
    output[4 * size] = '\0';
    printf("%s\n", output);
    free(output);
}
void merge_sort(int * arr, int low, int high){
    if (low < high){
        int mid = (high + low) / 2;
        merge_sort(arr, low, mid);
        merge_sort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}
void randomArraatGenerator(int * arr, int size){
    for(int i = 0; i < size; i++){
        arr[i] = i + 1;
    }
    time_t t;
    srand((unsigned) time (&t));
    for(int i = 0; i < size / 2; i++){
        int temp;
        temp = arr[i];
        int ran = rand() % size 
        arr[i] = arr[ran];
        arr[ran] = temp;
    }
}
void * pthread_merge_sort(void *){
    int low = 0;
    int high = size - 1;
    if (counter == 0){
        merge_sort(arr, 0, low + (high - low + 1) / 4);
    } else if(counter = 1){
        merge_sort(arr, low + (high - low + 1) / 4, (high + low) / 2);
    } else if(counter = 2){
        merge_sort(arr, (high - low) / 2 + 1, high - (high - low + 1) / 4);
    } else {
        merge_sort(arr, high - (high - low + 1) / 4 + 1, high - low);
    }
    counter++;
}
int main(){
    arr = malloc(sizeof(int) * size);
    randomArrayGenerator(arr, size);
    printf("The orginal array is: \n");
    printArr(arr, size);

    int low = 0;
    int high = size - 1;
    int pivot1 = low +(high - low + 1) / 4;
    int pivot2 = (high + low) / 2;
    int pivot3 = high - (high - low + 1) / 4;
    for(int i = 0; i < 4; i++){
        pthread_create(&threads[i], NULL, pthread_merge_sort, NULL);
    }
    printf("Sorted aray is: \n");
    printArr(arr, size);
    free(arr);
    return 0;
}