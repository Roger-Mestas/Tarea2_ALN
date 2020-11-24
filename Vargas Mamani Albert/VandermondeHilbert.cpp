#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <bits/stdc++.h>
#include <cstdlib>
using namespace std;


void vandermonde(double* v,int n,double** &vander){
    for (int i = 0; i < n; i++){
        for (int j = n-1; j >=0; j--){
            vander[i][j]=pow(v[i],j);
        }
    }
}

int main(){

    int n;

    cout<<"Tamano de vector"<<endl;
    cin>>n;

    double* vector = new double[n];
    double** vander = new double* [n];

    cout<<"valores"<<endl;
    for (int i = 0; i < n; i++){
        cin>>vector[i];
        vander[i]=new double [n];
    }

    vandermonde(vector,n,vander);


    cout.setf(ios::fixed);
	cout.precision(4);


    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cout<<setw(10)<<vander[i][j]<<"  ";
        }
        cout<<endl;
    }
}


/*
//Quitar los /* para que funcione la matriz

//Condicionamiento

void invermat(int, double**, double **, double &);
double norma(int, double**);
void elim_gauss(int, double**&, double**&);
void descompLU(int, double** &, double**&, double*&, double*&, double**&);

double ncond(int n, double** &a){
    double nmr_cond;
	double **ainv, determ, **a_org;

    a_org = new double* [n];
    for(int i=0; i<n; i++)
		a_org[i] = new double [n];


    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            a_org[i][j]=a[i][j];


	ainv = new double* [n];
	for(int j=0; j<n; j++)
		ainv[j] = new double [n];

	invermat(n, a, ainv, determ);

    if (determ == 0)
        cout<<"No tiene inversa"<<endl;


    cout<<" A = "<<norma(n,a_org)<<endl;
    cout<<" Inversa de A = "<<norma(n,ainv)<<endl;

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


void invermat(int n, double **a, double **ainv, double &determ){

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


    determ = 1.;
	for (int i = 0; i < n; i++) {
		determ = determ * a[i][i];
	}


    if (determ != 0){
        descompLU(n,a,L,D,X,ainv);
    }

    delete L, D, X;
}


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


void descompLU(int n, double** &a, double** &L, double* &D, double* &X, double** &ainv){

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i > j) {
              L[i][j] = a[i][j]/a[j][j];
              a[i][j] = 0;
           }
       }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
              L[j][j] = 1;
        }
    }

    for (int k = 0; k < n; k++) {

        for (int i = 0; i < n; i++) {
            if (i == k) L[i][n] = 1;
            else  L[i][n] = 0;
        }


        double sum;
        D[0] = L[0][n];

        for (int i = 1; i < n; i++) {
            sum = 0;
            for (int j = 0; j < i; j++)
                sum = sum + L[i][j]*D[j];
            D[i] = L[i][n] - sum;
        }


        for (int i = 0; i < n; i++) {
            a[i][n] = D[i];
        }


        X[n-1] = a[n-1][n]/a[n-1][n-1];


        for (int i = n - 2; i > -1; i--) {
            sum = 0;
            for (int j = i+1; j < n; j++)
                sum = sum + a[i][j]*X[j];
            X[i] = (a[i][n] - sum)/a[i][i];
        }


        for(int i = 0; i < n; i++){
            ainv[i][k] = X[i];
        }
    }
}


int main(){
    ifstream label1 ("condicimatriz.in");


	int i, j, n;
    label1 >> n;
    double** a;

    a = new double* [n];
    for(i=0; i<n; i++)
		a[i] = new double [n];

    for(i=0; i<n; i++)
        for(j=0; j<n; j++)
            label1 >> a[i][j];

	cout << "Matriz inicial\n\n";


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

//Quitar los /* para que funcione la matriz
void Hilbert(int n){
    float H[n][n];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {

            H[i][j] = (float)1.0 / ((i + 1) + (j + 1) - 1.0);
        }
    }


    cout.setf(ios::fixed);
	cout.precision(6);


    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout <<setw(10)<< H[i][j] << "\t";
        cout << endl;
    }
}


int main(){
    int n;
    cout<<"Tamano de matriz"<<endl;
    cin>>n;
    Hilbert(n);
    return 0;
}
*/
