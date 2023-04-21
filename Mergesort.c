#include <stdio.h>   //bibliotecas necesarias para el programa, que son stdio.h para las funciones de entrada/salida, 
#include <stdlib.h>  //stdlib.h para funciones de memoria dinámica y 
#include <time.h>    //time.h para la generación de números aleatorios.

// Función para mezclar dos subarreglos ordenados de un arreglo dado
void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;  // Tamaño del subarreglo izquierdo
    int n2 = r - m;      // Tamaño del subarreglo derecho

    int L[n1], R[n2];    // Arreglos temporales para almacenar los subarreglos

    // Copia los elementos del subarreglo izquierdo al arreglo temporal L[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    // Copia los elementos del subarreglo derecho al arreglo temporal R[]
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;

    // Mezcla los subarreglos ordenadamente en el arreglo original
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copia los elementos restantes del subarreglo izquierdo en el arreglo original
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copia los elementos restantes del subarreglo derecho en el arreglo original
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Función para ordenar un arreglo utilizando Merge Sort
void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;  // Calcula el índice medio del arreglo

        // Ordena recursivamente las dos mitades del arreglo
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        // Mezcla las dos mitades ordenadas del arreglo
        merge(arr, l, m, r);
    }
}

int main() {
    int n = 10;
    int arr[n];

    // Genera números aleatorios en el arreglo utilizando srand() y rand()
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100;  // Genera un número aleatorio entre 0 y 99
    }

    // Imprime el arreglo original
    printf("Arreglo original aleatorio: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    // Ordena el arreglo utilizando Merge Sort
    mergeSort(arr, 0, n - 1);

    // Imprime el arreglo ordenado
    printf("\nArreglo ordenado: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
