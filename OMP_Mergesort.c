#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>


void Merge(int * array, int n, int * temp);
void MergeSort(int * array, int n, int * temp);

int main()
{
   int n = 1000;
   double start_time, end_time;

   int data[n], temp[n];

   srand(time(NULL));

   for (int i = 0; i < n; i++)
   {
      data[i]=rand()%1000;
   } 


   printf("Arreglo antes de ordenamiento\n");
   for (int i = 0; i < n; i++)
   {
      printf("%d  ",data[i]);
   }

   start_time = omp_get_wtime();

   #pragma omp parallel num_threads(100)
   {
      #pragma omp single
      MergeSort(data, n, temp);
   }
   end_time = omp_get_wtime();

   printf("\nArreglo ordenado\n");
   
   for (int i = 0; i < n; i++)
   {
      printf("%d  ",data[i]);
   }

   printf("\nNumero de elementos a ordenar: %d",n);
   printf("\nTiempo de ejecucion: %g segundos\n",end_time-start_time);
   
   return 0;
}

void Merge(int * array, int n, int * temp) {
   int a = 0;
   int b = n/2;
   int ti = 0;
	//a itera hasta la primera mitad y b itera la segunda mitad del arreglo
   while (a<n/2 && b<n) {
      if (array[a] < array[b]) {
         temp[ti] = array[a];
         ti++; 
         a++;
      } else {
         temp[ti] = array[b];
         ti++; 
	      b++;
      }
   }
   while (a<n/2) { //primera mitad
      temp[ti] = array[a];
	   ti++;
	   a++;
   }
   while (b<n) { //segunda mitad
      temp[ti] = array[b];
      ti++; 
	   b++;
   }

   memcpy(array, temp, n*sizeof(int));    //copia el arreglo ordenado en el arreglo original

}


void MergeSort(int * array, int n, int * temp)
{
   if (n < 2) return;

   #pragma omp task firstprivate (array, n, temp)
   MergeSort(array, n/2, temp);

   #pragma omp task firstprivate (array, n, temp)
   MergeSort(array+(n/2), n-(n/2), temp);
	
   
   #pragma omp taskwait                   //directiva que espera que ambas tareas terminen su ejecucion

   
   Merge(array, n, temp);                 //fusion de los arreglos ordenados
}