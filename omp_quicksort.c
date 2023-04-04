#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#define n 10000 


void quicksort(int arr[], int low, int high);
int partition(int arr[], int low, int high);
void swap(int* a, int* b);

int main() {
    int arr[n];
    int i, j;

     srand(time(0));

    for (j = 0; j < n; j++){
      arr[j] = rand() % 100;    
    } 

    double start_time = omp_get_wtime();

    #pragma omp parallel num_threads(4)
    {
        #pragma omp single
        quicksort(arr, 0, n - 1);
    }

    double end_time = omp_get_wtime();

    printf("Arreglo ordenado: ");
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    printf("\nTiempo de ejecución: %f segundos\n", end_time - start_time);
    return 0;
}

void quicksort(int arr[], int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);

        #pragma omp parallel sections
        {
             #pragma omp section
            quicksort(arr, low, pivotIndex - 1);
             #pragma omp section
            quicksort(arr, pivotIndex + 1, high);
        }
    }
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}


