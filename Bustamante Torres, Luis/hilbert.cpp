#include <bits/stdc++.h> 
#include <iomanip>

using namespace std; 
  
// Funcion para generar la matriz de Hilbert
void Hilbert(int n){ 
    float H[n][n]; 
  
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            //Se usa la formula para generar la matriz de Hilbert
            H[i][j] = (float)1.0 / ((i + 1) + (j + 1) - 1.0); 
        } 
    } 

    //Para la parte decimal
    cout.setf(ios::fixed);
	cout.precision(6);
  
    //Imprime la matriz de Hilbert
    for (int i = 0; i < n; i++) { 
        for (int j = 0; j < n; j++)  
            cout <<setw(10)<< H[i][j] << "\t";         
        cout << endl; 
    } 
}
  
//Funcion main
int main(){ 
    int n;
    cout<<"Ingrese el tamaño"<<endl;
    cin>>n; 
    Hilbert(n); 
    return 0; 
} 