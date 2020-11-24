#include <iostream>  //Para la entrada y salida
#include <cmath>   //Para operaciones matematicas como pow(potencia)
#include <iomanip> //Para la salida

using namespace std;

//Funcion para la matriz de vandermonde
void vandermonde(double* v,int n,double** &vander){
    for (int i = 0; i < n; i++){
        for (int j = n-1; j >=0; j--){
            vander[i][j]=pow(v[i],j);  //Potencia decreciente
        }
    }
}

int main(){
    //{ 1, 1.5, 2, 2.5, 3 } ;
    int n;

    cout<<"Ingrese el tamaño del vector"<<endl;
    cin>>n;

    double* vector = new double[n]; //Se asigna memoria para el vector
    double** vander = new double* [n];

    cout<<"Ingrese los valores"<<endl;
    for (int i = 0; i < n; i++){
        cin>>vector[i];
        vander[i]=new double [n];  //Se asigna memoria para la matriz de vandermonde
    }

    vandermonde(vector,n,vander);

    //Para imprimir
    cout.setf(ios::fixed);
	cout.precision(4);
    
    //Para imprimir
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cout<<setw(10)<<vander[i][j]<<"  ";
        }
        cout<<endl;
    }
}