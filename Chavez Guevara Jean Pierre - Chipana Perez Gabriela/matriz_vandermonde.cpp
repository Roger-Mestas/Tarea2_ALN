#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

void vandermonde(int m,int n)
{
    double x[m];
    for (int l = 0; l < m; l++) 
    {
        double f;
        cin >> f;
        x[l] = f;
    }
    vector<vector<double> > mat (m , vector<double>( n, 0));
    for ( int i = 0; i < m; i++) 
        for (int j = 0; j < n; j++)
            {
                mat [i][j] = pow(x[i] , j);
            }

    for (int i = 0 ; i < m ; ++i) 
    {
        for (int j = 0 ; j < n ; ++j)
            cout << mat [ i ] [ j ] << " " ;

                cout << "\n" ;
    }

}

int main ()
{
    int m, n;
    cout<<"Ingresar tamaño m,n:"<<endl;
    cin >> m;
    cin >> n;
    vandermonde(m,n);
    return 0;
}