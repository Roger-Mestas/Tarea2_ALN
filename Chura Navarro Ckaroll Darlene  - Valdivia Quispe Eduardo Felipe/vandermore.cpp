#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void createVandermonde(int *iarr, int **vander, int nx){
    for(int i = 0; i < nx; i++)
        for(int j = 0; j < nx; j++)
            vander[i][j] = pow(iarr[i], nx - j - 1);
}

int **array2_create(int row, int col){
    int **arr=NULL;
    arr = (int **) malloc((row*sizeof(int*)));
    if (!arr) {
        fprintf(stderr, "matrixi_create : error allocation row");
        exit(0);
    }
    arr[0]=(int*) malloc((row*col)*sizeof(int));
    if (!arr[0]) {
        fprintf(stderr, "matrixi_create : error allocation column");
        exit(0);
    }
    for(int i=1; i<row; i++)
        arr[i]=arr[i-1] + col;
    return arr;
}

void array2_free(int **arr){
    free(arr[0]);
    free(arr);
}

void printArray2(int **arr, int nx, int ny){
    for(int i = 0; i < ny; i++){
        for(int j = 0; j < nx; j++)
            printf("%i \t", arr[i][j]);
        std::cout << std::endl;    
    }
    std::cout << std::endl;
}

void printArray1(int *arr, int nx){
    for(int i = 0; i < nx; i++)
        printf("%i \t", arr[i]);
    std::cout << std::endl;
    std::cout << std::endl;
}

int main(int argc, char **argv){
    int nx = 5;
    int *iarr, **vandermonde;
  
    vandermonde = array2_create(nx, nx);
    iarr = (int*) calloc (nx, sizeof(int));
    for(int i = 0; i < nx; i++)
        iarr[i] = i + 1;
  
    createVandermonde(iarr, vandermonde, nx);
    printArray1(iarr, nx);
    printArray2(vandermonde, nx, nx); 
    free(iarr);
    array2_free(vandermonde);
}
