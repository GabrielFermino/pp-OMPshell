#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <time.h>

void insertionSort(int a[], int n, int auxM);
void shellSort(int a[], int n);

int main(){
    long int n = 850000000;
    int *vet;

    double start, fim;
    start = omp_get_wtime();
    vet = (int *)malloc(n*sizeof(int));
    srand(time(NULL));

    for (int i = 0; i < n; i++){
        vet[i] = rand() + 1;
    }

    shellSort(vet,n);

    fim = omp_get_wtime();

    printf("Tempo gasto: %lf segundos \n", fim - start);

    return 0;
}

void shellSort(int a[], int n){

    int i, m;

        while(m < n){
        m = 3*m+1;
    }
    omp_set_num_threads(4);
    for(m = n/3; m > 0; m /= 3)
    {
          #pragma omp parallel for shared(a,m,n) private (i)
            for(i = 0; i < m; i++)
                insertionSort(&(a[i]), n-i, m);
    }
}

void insertionSort(int a[], int n, int auxM){

    int j;
    for (j=auxM; j<n; j+=auxM) {
        int val = a[j];
        int i = j - auxM;
        while (i >= 0 && a[i] > val) {
            a[i+auxM] = a[i];
            i = i - auxM;
        }
	a[i+auxM] = val;
    }
}

