#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define n 1000

void swap(int *a, int *b);
int partition(int arr[], int low, int high);
void quicksort(int arr[], int low, int high);


int main() {
    int i, j;
    int arr[n];

    srand(time(0));

    for (j = 0; j < n; j++){
      arr[j] = rand() % 100;    
    } 

     double start_time = clock();

    quicksort(arr, 0, n - 1);

    double end_time = clock();

    printf("Arreglo ordenado: ");
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    double time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;

    printf("\nNumero de elementos a ordenar: %d\n", n);

    printf("\nTiempo de ejecución: %f segundos\n", time);
    return 0;
}

void quicksort(int arr[], int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);

        quicksort(arr, low, pivotIndex - 1);
        quicksort(arr, pivotIndex + 1, high);
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

