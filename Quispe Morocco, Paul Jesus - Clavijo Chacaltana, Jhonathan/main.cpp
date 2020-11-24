#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <cmath>

using namespace std;

void pedir_datos();
void Cofactor(double **A, double **temp, int p, int q, int n);
double determinante(double **A, int m);
void adjunto(double **A, double **adj);
bool inversa(double **A, double **C);
template<class T>
void display(T **A);
void matriz_inicial(double **A);
void Hilbert(double **H);
void Vandermonde(double **V);
double Norma2(double **A, double **B);
double Norma1(double **A, double **B);
double Norma_infinito(double **A, double **B);
double **A, **H, **V, **temp, **adj, **C;
int n;

int main()
{
    setlocale(LC_ALL, "");
    int opc;
    pedir_datos();
    cout << "Ingrese el numero de la opcion:" << endl;
    cin >> opc;
    while(opc != 4)
    {
        switch(opc)
        {
            case 1:
                cout << "\nMatriz ordinaria :" << endl;
                matriz_inicial(A);
                cout << "\nLa matriz ingresada es :" << endl;
                display(A);
                cout << "\nLa inversa es :\n" << endl;
                if(inversa(A, C))
                {
                    display(C);
                    cout << "\nNumero de condiciones con la Norma 1 es :" << endl;
                    cout << Norma1(A, C);
                    cout << "\nNumero de condiciones con la Norma 2 es :" << endl;
                    cout << Norma2(A, C);
                    cout << "\nNumero de condiciones con la Norma infinito es :" << endl;
                    cout << Norma_infinito(A, C);
                }
                break;
            case 2:
                cout << "\nMatriz Hilbert :" << endl;
                Hilbert(A);
                display(A);
                cout << "\nLa inversa es :\n" << endl;
                if(inversa(A, C))
                {
                    display(C);
                    cout << "\nNumero de condiciones con la Norma 1 es :" << endl;
                    cout << Norma1(A, C);
                    cout << "\nNumero de condiciones con la Norma 2 es :" << endl;
                    cout << Norma2(A, C);
                    cout << "\nNumero de condiciones con la Norma infinito es :" << endl;
                    cout << Norma_infinito(A, C);
                }
                break;
            case 3:
                cout << "\nMatriz Vandermonde :" << endl;
                Vandermonde(A);
                display(A);
                cout << "\nLa inversa es :\n" << endl;
                if(inversa(A, C))
                {
                    display(C);
                    cout << "\nNumero de condiciones con la Norma 1 es :" << endl;
                    cout << Norma1(A, C);
                    cout << "\nNumero de condiciones con la Norma 2 es :" << endl;
                    cout << Norma2(A, C);
                    cout << "\nNumero de condiciones con la Norma infinito es :" << endl;
                    cout << Norma_infinito(A, C);
                }
                break;
            default: cout << "Opcion Invalida." << endl;
        }
        pedir_datos();
        cout << "Ingrese el numero de la opcion:" << endl;
        cin >> opc;
    }
    cout << "Programa finalizado" << endl;

    for(int i = 0; i < n; i++)
    {
		delete[] A[i];
	}
	delete[] A;
    for(int i = 0; i < n; i++)
    {
		delete[] temp[i];
	}
	delete[] temp;
    for(int i = 0; i < n; i++)
    {
		delete[] adj[i];
	}
	delete[] adj;
    for(int i = 0; i < n; i++)
    {
		delete[] C[i];
	}
	delete[] C;
    for(int i = 0; i < n; i++)
    {
		delete[] H[i];
	}
	delete[] H;
    for(int i = 0; i < n; i++)
    {
		delete[] V[i];
	}
	delete[] V;
    return 0;
}

void pedir_datos()
{
    cout << "\n\t\t\t_____________________" << endl;
    cout << "\t\t\tNumero de condiciones" << endl;
    cout << "\t\t\t_____________________\n\n";
    cout << endl;
    cout << "Dimension de la matriz: ";
    cin >> n;
    cout << "\n\n\t\t\t---------------------------------------------------------" << endl;
    cout << "\t\t\t|\tN°opcion\t|\topcion\t\t\t|" << endl;
    cout << "\t\t\t|-----------------------|-------------------------------|" << endl;
    cout << "\t\t\t|\t1\t\t|\tmatriz ordinaria\t|" << endl;
    cout << "\t\t\t|\t2\t\t|\tmatriz Hilbert\t\t|" << endl;
    cout << "\t\t\t|\t3\t\t|\tmatriz Vandermonde\t|" << endl;
    cout << "\t\t\t|\t4\t\t|\tSalir\t\t\t|" << endl;
    cout << "\t\t\t---------------------------------------------------------\n\n" << endl;
    A = new double*[n];
    for(int i = 0; i < n; i++)
    {
        A[i] = new double[n];
    }
    temp = new double*[n];
    for(int i = 0; i < n; i++)
    {
        temp[i] = new double[n];
    }
    adj = new double*[n];
    for(int i = 0; i < n; i++)
    {
        adj[i] = new double[n];
    }
    C = new double*[n];
    for(int i = 0; i < n; i++)
    {
        C[i] = new double[n];
    }
    H = new double*[n];
    for(int i = 0; i < n; i++)
    {
        H[i] = new double[n];
    }
    V = new double*[n];
    for(int i = 0; i < n; i++)
    {
        V[i] = new double[n];
    }
}

void Cofactor(double **A, double **temp, int p, int q, int n)
{
    int i = 0, j = 0;
    for (int f = 0; f < n; f++)
    {
        for (int c = 0; c < n; c++)
        {
            if (f != p && c != q)
            {
                *(*(temp+ i)+ j++) = *(*(A + f)+ c);
                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

double determinante(double **A, int n)
{
    double D = 0;
    if (n == 1)
        return **A;
    double **temp1;
    temp1 = new double*[n];
    for(int i = 0; i < n; i++)
    {
        temp1[i] = new double[n];
    }
    double sign = 1;
    for (int f = 0; f < n; f++)
    {
        Cofactor(A, temp1, 0, f, n);
        D += sign * (*(*(A)+ f)) * determinante(temp1, n - 1);
        sign = -sign;
    }
    return D;
    for(int i = 0; i < n; i++)
    {
		delete[] temp1[i];
	}
	delete[] temp1;
}

void adjunto(double **A, double **adj)
{
    if (n == 1)
    {
        **adj = 1;
        return;
    }
    double sign = 1, **temp1;
    temp1 = new double*[n];
    for(int i = 0; i < n; i++)
    {
        temp1[i] = new double[n];
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            Cofactor(A, temp1, i, j, n);
            sign = ((i + j)%2==0)? 1: -1;
            *(*(adj + j)+ i) = (sign)*(determinante(temp1, n-1));
        }
    }
    for(int i = 0; i < n; i++)
    {
		delete[] temp1[i];
	}
	delete[] temp1;
}

bool inversa(double **A, double **C)
{
    double det = determinante(A, n);
    if (det == 0)
    {
        cout << "Matriz singular, no se puede hallar su inversa";
        return false;
    }
    double **adj1;
    adj1 = new double*[n];
    for(int i = 0; i < n; i++)
    {
        adj1[i] = new double[n];
    }
    adjunto(A, adj1);
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
            *(*(C+i)+j) = *(*(adj1+i)+j)/double(det);

    return true;
    for(int i = 0; i < n; i++)
    {
		delete[] adj1[i];
	}
	delete[] adj1;
}

template<class T>
void display(T **A)
{
    for (int i = 0; i < n; i++)
    {
        cout << " [";
        for (int j=0; j<n; j++)
        {
            cout << *(*(A + i)+ j) << " ";
        }
        cout << "]" << endl;
    }
}

void matriz_inicial(double **A)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cout << "Ingrese elemento en la posicion [" << i << "] [" << j << "]:" << endl;
            cin >> *(*(A + i)+ j);
        }
    }
}

void Hilbert(double **H)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            *(*(H + i)+ j) = (double)1.0/((i+1)+(j+1)-1.0);
        }
        cout << endl;
    }
}

void Vandermonde(double **V)
{
    int x = 1;
    for(int i = 0; i < n; i++)
    {
        *(*(V + i)) = 1;
        for(int j = 1; j < n; j++)
        {
            *(*(V + i) + j) = *(*(V + i)+ j-1) * x;
        }
        x++;
    }
}

double Norma2(double **A, double **B)
{
    double sum1=0, sum2=0;
    for(int i = 0 ; i<n ; i++){
        for(int j = 0 ; j < n ; j++){
            sum1 = *(*(A + i)+ j) * *(*(A + i)+ j) + sum1;
            sum2 = *(*(B + i)+ j) * *(*(B + i)+ j) + sum2;
        }
    }
    sum1 = sqrt(sum1);
    sum2 = sqrt(sum2);
    return sum1*sum2;
}

double Norma1(double **A, double **B)
{
    double max1=0, max2=0 , sum1, sum2;
    for(int i = 0; i < n; i++)
    {
        sum1 = 0;
        sum2 = 0;
        for(int j = 0; j < n; j++)
        {
            sum1 = abs(*(*(A + j)+ i)) + sum1;
            sum2 = abs(*(*(B + j)+ i)) + sum2;
        }
        if(sum1 > max1)
        {
            max1 = sum1;
        }
        if(sum2 > max2)
        {
            max2 = sum2;
        }
    }
    return max1*max2;
}

double Norma_infinito(double **A, double **B)
{
    double max1=0, max2=0 , sum1, sum2;
    for(int i = 0; i < n; i++)
    {
        sum1 = 0;
        sum2 = 0;
        for(int j = 0; j < n; j++)
        {
            sum1 = abs(*(*(A + i)+ j)) + sum1;
            sum2 = abs(*(*(B + i)+ j)) + sum2;
        }
        if(sum1 > max1)
        {
            max1 = sum1;
        }
        if(sum2 > max2)
        {
            max2 = sum2;
        }
    }
    return max1*max2;
}
