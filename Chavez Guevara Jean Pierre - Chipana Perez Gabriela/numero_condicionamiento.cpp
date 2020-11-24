#include<bits/stdc++.h>
#include<iostream>
using namespace std; 
const int MAX = 100;

double Normal(double mat[][MAX], int n) 
{ 
    double sum = 0; 
    for (int i=0; i<n; i++) 
        for (int j=0; j<n; j++) 
            sum += mat[i][j]*mat[i][j]; 
    return sqrt(sum); 
}

double Normal_inverse(double mat_inv[][MAX], int n)
{
    double sum_inverse = 0; 
    for (int i=0; i<n; i++) 
        for (int j=0; j<n; j++) 
            sum_inverse += mat_inv[i][j]*mat_inv[i][j]; 
    return sqrt(sum_inverse);
}

void Inverse_Matrix(float** matrix, int order)
{
 
    float temp;

    for (int i = 0; i < order; i++) {
 
        for (int j = 0; j < 2 * order; j++) {

            if (j == (i + order))
                matrix[i][j] = 1;
        }
    }

    for (int i = order - 1; i > 0; i--) {

        if (matrix[i - 1][0] < matrix[i][0]) {
            float* temp = matrix[i];
            matrix[i] = matrix[i - 1];
            matrix[i - 1] = temp;
        }
    }
 

    for (int i = 0; i < order; i++) {
 
        for (int j = 0; j < order; j++) {
 
            if (j != i) {
 
                temp = matrix[j][i] / matrix[i][i];
                for (int k = 0; k < 2 * order; k++) {
 
                    matrix[j][k] -= matrix[i][k] * temp;
                }
            }
        }
    }
 
 
    for (int i = 0; i < order; i++) {
 
        temp = matrix[i][i];
        for (int j = 0; j < 2 * order; j++) {
 
            matrix[i][j] = matrix[i][j] / temp;
        }
    }

    for (int i = 0; i < order; i++) {
        for (int j = order; j < 2 * order; j++) {
            printf("%.3f  ", matrix[i][j]);
        }
        printf("\n");
    }
    return;
}

int main()
{
    
    cout<<"....Programa para hallar el numero de condicionamiento...."<<endl;
    double mat[][MAX] = {{5, 7, 9, 4, 2}, 
        {4, 3, 8, 3, 9}, 
        {7, 5, 6, 5, 1}, 
        {2, 7, 6, 6, 2}, 
        {7, 8, 3, 6, 4}, 
    };
    cout<<"Primer paso: hallar la normal de la matriz..."<<endl;  
    cout<<"Normal = "<<Normal(mat, 5)<<endl;
    cout<<"Segundo paso: hallar la normal de la inversa..."<<endl;
    int order = 5;
    float** matrix = new float*[20];
    for (int i = 0; i < 20; i++)
        matrix[i] = new float[20];
 
    matrix[0][0] = 5;
    matrix[0][1] = 7;
    matrix[0][2] = 9;
    matrix[0][3] = 4;
    matrix[0][4] = 2;
    matrix[1][0] = 4;
    matrix[1][1] = 3;
    matrix[1][2] = 8;
    matrix[1][3] = 3;
    matrix[1][4] = 9;
    matrix[2][0] = 7;
    matrix[2][1] = 5;
    matrix[2][2] = 6;
    matrix[2][3] = 5;
    matrix[2][4] = 1;
    matrix[3][0] = 2;
    matrix[3][1] = 7;
    matrix[3][2] = 6;
    matrix[3][3] = 6;
    matrix[3][4] = 2;
    matrix[4][0] = 7;
    matrix[4][1] = 8;
    matrix[4][2] = 3;
    matrix[4][3] = 6;
    matrix[4][4] = 4;
    
    Inverse_Matrix(matrix, order);
    cout<<"Sacarle la norma a la inversa de la matriz resultante:"<<endl;
    double mat_inv[][MAX] = {{0.017, -0.006, 0.123, -0.171,  0.060}, 
        {0.240, -0.085, -0.275, -0.057, 0.168}, 
        {0.081, 0.030, 0.051, 0.020, -0.131}, 
        {-0.353, 0.036, 0.261, 0.274, -0.108}, 
        {-0.042, 0.103, -0.095, -0.015, 0.070}, 
    };
    cout<<"Normal inversa ="<<Normal_inverse(mat_inv, 5)<<endl;
    cout<<"Tercer paso :multiplicar la normal por la normal inversa..."<<endl;
    double nmr_cond = Normal(mat,5) * Normal_inverse(mat_inv,5);
    cout<<"El numero de condicionamiento es:"<<nmr_cond;
    return 0;
}
