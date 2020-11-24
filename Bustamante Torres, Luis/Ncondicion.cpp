//////////////////////////////////////////////////////////////////////////
/*  Entrar al archivo matriz.in para modificar los valores de la matriz */ 
//////////////////////////////////////////////////////////////////////////


#include <iostream>  //Libreria para la salida del programa
#include <fstream>  //Para leer la matriz desde el fichero
#include <cstdlib>  //Libreria estandar de C
#include <iomanip> //Para manipular la parte decimal de un numero
#include <cmath>  //Libreria para funciones matematicas

//Espacio de nombres para usar las funciones std::
using namespace std;

//Declaracion de las funciones
void invermat(int, double**, double **, double &);
double norma(int, double**);
void elim_gauss(int, double**&, double**&);
void descompLU(int, double** &, double**&, double*&, double*&, double**&);

//Funcion para el numero de condicionamiento de la matriz
double ncond(int n, double** &a){
    double nmr_cond;
	double **ainv, determ, **a_org; //Crea las matrices para el procedimiento

    //Asigna memoria para la matriz original
    a_org = new double* [n];
    for(int i=0; i<n; i++)
		a_org[i] = new double [n];

    //Realiza una copia para mantener los valores originales de la matriz
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            a_org[i][j]=a[i][j];
        
    //Asigna memoria para las matrices
	ainv = new double* [n];
	for(int j=0; j<n; j++)
		ainv[j] = new double [n];

	invermat(n, a, ainv, determ);

    if (determ == 0)
        cout<<"No tiene inversa"<<endl;

    //El numero de condicion es la multiplicacion de las normas 
    //de la matriz y su inversa
    cout<<"Norma A = "<<norma(n,a_org)<<endl;
    cout<<"Norma A inversa = "<<norma(n,ainv)<<endl;

    nmr_cond = norma(n,a_org) * norma(n,ainv);

    return nmr_cond;
}

double norma(int n, double** matriz){
    double norma,sum;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            sum+=(matriz[i][j] * matriz[i][j]);

    norma=sqrt((double)sum);
    return norma;
}

//Funcion para hallar la matriz inversa
void invermat(int n, double **a, double **ainv, double &determ){
    //Para almacenar lso valores de las descomposiciones
    double **L, *D, *X;
	X = new double [n]; 
    D = new double [n];
	L = new double* [n];
	
	for (int j = 0; j < n; j++) 
		L[j] = new double [n];

    elim_gauss(n,a,L);
    determ = 1.;
	for (int i = 0; i < n; i++) {
		determ = determ * a[i][i];
	}

    //Para hallar el determinante
    determ = 1.;
	for (int i = 0; i < n; i++) {
		determ = determ * a[i][i];
	}

    //Si tiene inversa 
    if (determ != 0){
        descompLU(n,a,L,D,X,ainv);
    }
    //Se libera la memoria
    delete L, D, X;  
}

//Eliminacion gaussiana para la funcion "invermat"
void elim_gauss(int n, double** &a, double** &L){
	int i, j, k;
	double factor;

	for (k = 0; k < n - 1; k++) {
		for (i = k+1; i < n;  i++) {
			factor = a[i][k]/a[k][k]; 
			for (j = k+1; j < n + 1; j++) {
				a[i][j] = a[i][j] - factor * a[k][j];
			}
		}
	}
}

//Descomposicion LU para hallar la inversa
void descompLU(int n, double** &a, double** &L, double* &D, double* &X, double** &ainv){
    //Para hallar el pivot
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i > j) {
              L[i][j] = a[i][j]/a[j][j];
              a[i][j] = 0;
           }
       }
    }

    //Inicializa la matriz L en 1
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
              L[j][j] = 1;
        }
    }

    for (int k = 0; k < n; k++) {
        //Inicializa los valores L[i][n] para la matriz L
        for (int i = 0; i < n; i++) {
            if (i == k) L[i][n] = 1;
            else  L[i][n] = 0;
        }

        //Sustitución hacia adelante
        double sum;
        D[0] = L[0][n];

        for (int i = 1; i < n; i++) {
            sum = 0;
            for (int j = 0; j < i; j++)
                sum = sum + L[i][j]*D[j];
            D[i] = L[i][n] - sum;
        }

        // Esta parte asigna lo producido de la sustitucion hacia adelante a la matriz U
        for (int i = 0; i < n; i++) {
            a[i][n] = D[i];
        }

        // Sustitucion hacia atras
        X[n-1] = a[n-1][n]/a[n-1][n-1];

        //Determinación de las raíces restantes
        for (int i = n - 2; i > -1; i--) {
            sum = 0;
            for (int j = i+1; j < n; j++) 
                sum = sum + a[i][j]*X[j];
            X[i] = (a[i][n] - sum)/a[i][i];
        }

        //Asigna los valores a la matriz inversa
        for(int i = 0; i < n; i++){
            ainv[i][k] = X[i];
        }
    }  
}

//Funcion main
int main(){
    ifstream label1 ("matriz.in"); // Abre el archivo de entrada para leer la matriz

	// Definición de variables y asignación dinámica de memoria	
	int i, j, n;
    label1 >> n; //Para leer el tamaño de la matriz
    double** a; //Matriz inicial

    a = new double* [n];
    for(i=0; i<n; i++)
		a[i] = new double [n];

    for(i=0; i<n; i++)
        for(j=0; j<n; j++)
            label1 >> a[i][j];        

	cout << "Matriz inicial\n\n";

	//Imprime la matriz inicial
	for(i=0; i<n; i++){
        for(j=0; j<n; j++)
            cout <<  a[i][j] <<"\t";
	    cout << endl;
    }
	cout << endl;

    double n_cond=ncond(n,a);

    cout <<"Numero de condicion = "<<setw(8) << n_cond <<endl;


	delete a;
	return 0;
}

