// programa en C++ para hallar matrices de vandermonde
#include <iostream> 
#include <math.h>
using namespace std; 
  
// Funcion que genera la matriz de vandermonde
void printMatrixVander(int n) 
{
	//vector que podria ser ingresado manualmente pero a efectos de practicidad se genera en el codigo
	int vec[n];
	for(int k=0; k<n; k++)
    	vec[k] = k+1;

    float V[n][n]; 
    for (int i = 0; i < n; i++) { 
        for (int j = 0; j < n; j++) { 
            // usamos la potencia decreciente para hallar cada elemento de la matriz
            V[i][j] = pow(vec[i], n-j-1);
        } 
    } 
    // imprimimos la matriz
    for (int i = 0; i < n; i++) { 
        for (int j = 0; j < n; j++)  
            cout << V[i][j] << " ";         
        cout << "\n";
    } 
} 
  
// programa principal
int main() 
{
    unsigned int n;
    cout<<"Halla matriz de Vandermonde\nTamaño:";
    cin>>n;
    printMatrixVander(n); 
    return 0; 
} 