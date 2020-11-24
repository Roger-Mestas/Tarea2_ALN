#include <iostream> 
#include <conio.h>
#include <bits/stdc++.h> 
#include <iomanip>
#include <cmath> 

using namespace std; 

    void Factor(double M[100][100], double t[][100], int p, int q, int n) {
       int i = 0, j = 0;
        for (int r= 0; r< n; r++) {
            for (int c = 0; c< n; c++){
                if (r != p && c != q) { 
                    t[i][j++] = M[r][c];
                    if (j == n-1) {j=0;i++;}
                }
            }
        }
    }

    double determinante(double M[100][100], int n){
        double D = 0;
        if (n == 1)
            return M[0][0];
        double t[n][100];
        double s = 1; 
        for (int i=0; i<n; i++){
            Factor(M, t, 0, i, n);
            D += s*M[0][i]*determinante(t, n - 1);
            s = -s;
        }
        return D;
    }

    void ADJ(double M[100][100],double adj[100][100],int n)
    {
        if (n == 1) {adj[0][0] = 1; return;}
        double s = 1;
        double t[n][100];
        for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
                Factor(M, t, i, j, n);
                s = ((i+j)%2==0)? 1: -1; 
                adj[j][i] = (s)*(determinante(t, n-1));
            }
        }
    }


    bool INV(double M[100][100], double inv[100][100],int n) {
        cout<<"Entrando determinante"<<endl;
        double det = determinante(M, n);
        if (det == 0) {
            cout << "\nNo se puede hallar inversa\n";
            return false;
        }
        double adj[n][100]; 
        ADJ(M, adj,n);
        for (int i=0; i<n; i++) for (int j=0; j<n; j++) inv[i][j] = adj[i][j]/double(det);
        return true;
    }


    template<class T> void print(T A[][100],int n) 
    {
        for (int i=0; i<n; i++) { 
            for (int j=0; j<n; j++) 
                cout << A[i][j] << " "; 
        cout << endl;
       }
    }


    double Abs(double x)
    {
        if(x<0)
            x=x*-1;
        return x;
    }


    void Matriz(double A[100][100], int n) {  
        for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                    cout<<" * "<<i+1<<j+1<<": ";
                    cin>>A[i][j];
                }
        }
    } 


    double NormaFrobenius(double A[100][100],int n){
        double sum=0;
        for(int i=0 ; i<n ; i++){
            for(int j=0 ; j<n ; j++){
                sum=pow(A[j][i],2)+sum;
            }
        }
        return sqrt(sum);
    }


    double CONDICIONAL2(double A[100][100],double B[100][100],int n){
        double max1=0, max2;
        max1=NormaFrobenius(A,n);
        max2=NormaFrobenius(B,n);
        return max1*max2;
    }

    double maxSumXCol(double A[100][100],int n){
        double max=0,sum;
        for(int i=0 ; i<n ; i++){
            sum=0;
            for(int j=0 ; j<n ; j++){
                sum=Abs(A[j][i])+sum;
            }
            if(sum>max)
                max=sum;
        }
        return max;
    }


    double CONDICIONAL1(double A[100][100],double B[100][100],int n){
        double max1=0, max2;
        max1=maxSumXCol(A,n);
        max2=maxSumXCol(B,n);
        return max1*max2;
    }


    double maxSumXFila(double A[100][100],int n){
        double max=0,sum;
        for(int i=0 ; i<n ; i++){
            sum=0;
            for(int j=0 ; j<n ; j++){
                sum=Abs(A[i][j])+sum;
            }
            if(sum>max)
                max=sum;
        }
        return max;
    }
    double CondInf(double A[100][100],double B[100][100],int n){
        double max1=0, max2;
        max1=maxSumXFila(A,n);
        max2=maxSumXFila(B,n);
        return max1*max2;
    }
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
            cout<<"|";
            for (int j = 0; j < n; j++)
                cout <<setw(10)<< H[i][j];
            cout<<"  |";       
            cout << endl; 
        } 
    }

    void vandermonde(int n){
	    double* vector = new double[n];
        double** vander = new double* [n];

	    cout<<"Ingrese los valores"<<endl;
        for (int i = 0; i < n; i++){
            cin>>vector[i];
            vander[i]=new double [n];
        }
    

        for (int i = 0; i < n; i++){
            for (int j = n-1; j >=0; j--){
                vander[i][j]=pow(vector[i],j);
            }
        }
        cout.setf(ios::fixed);
	    cout.precision(4);

        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                cout<<setw(10)<<vander[i][j]<<"  ";
            }
            cout<<endl;
        }
    
    }

    void primera(double A[100][100],double B[100][100],int n){
        
        Matriz(A,n);
        cout<<"\nResultado:\n";
        if(INV(A,B,n)==true){
            cout<<"CONDICIONAL 1:\t\t";
            cout<<CONDICIONAL1(A,B,n);
            cout<<"\CONDICIONAL 2 o Frobenious:\t";
            cout<<CONDICIONAL2(A,B,n);
            cout<<"\nNorma infinito:\t\t";
            cout<<CondInf(A,B,n);
        }

    }


int main(){

    cout<<"\n\n";
    cout<<"			+-------------------------------+"<<endl;
	cout<<"			|             MATRICES          |"<<endl;
	cout<<"			+-------------------------------+\n\n"<<endl;
    
    system("pause");
    system("cls");
    int op;
    int n;
    cout<<"Matriz orden mxm : "<<endl;
    cin>>n;
    double A[n][100],B[n][100];
    system("cls");
    do
    {
        int dato;
        cout<<"\n MENU--\n";
        cout<<"1) Hilbert"<<endl;
        cout<<"2) Vandermonde"<<endl;
        cout<<"3) Numero Condicionamiento"<<endl;
        cout<<"4) salir"<<endl;
        cout<<"\n opcion: ";
        cin>>op;
        switch (op)
        {
        case 1:
            Hilbert(n);
            system("pause");
            break;
        case 2:
	        vandermonde(n);
            system("pause");
            break;
        case 3:
            primera(A,B,n);
            system("pause");
            break;
        default:
            break;
        }
        system("cls");
    } while (op!=4);
    getch();
    return 0; 
} 