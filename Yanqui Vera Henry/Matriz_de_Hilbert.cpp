// programa en C++ para hallar matrices de hilbert
#include <iostream> 
using namespace std; 
  
// Funcion que genera la matriz de hilbert
void printMatrixHilbert(int n) 
{ 
    float H[n][n]; 
  
    for (int i = 0; i < n; i++) { 
        for (int j = 0; j < n; j++) { 
  
            // usamos la formula para hallar cada elemento de la matriz
            H[i][j] = (float)1.0 / ((i + 1) + (j + 1) - 1.0); 
        } 
    } 
    // imprimimos la matriz
    for (int i = 0; i < n; i++) { 
        for (int j = 0; j < n; j++)  
            cout << H[i][j] << " ";         
        cout << "\n";
    } 
} 
  
// programa principal
int main() 
{
    unsigned int n;
    cout<<"Halla matriz de Hilbert\nTamaño:";
    cin>>n;
    printMatrixHilbert(n); 
    return 0; 
} 