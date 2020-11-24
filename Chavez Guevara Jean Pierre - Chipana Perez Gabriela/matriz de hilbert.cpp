#include <bits/stdc++.h> 
using namespace std; 

void HilbertMatrix(int m) 
{ 
    float H[m][m]; 
    for (int i = 0; i < m; i++) 
    { 
        for (int j = 0; j < m; j++) 
        { 
            H[i][j] = (float)1.0 / ((i + 1) + (j + 1) - 1.0); 
        } 
    } 
    for (int i = 0; i < m; i++) 
    { 
        for (int j = 0; j < m; j++)
        {
            cout<<H[i][j] << " ";
        }        
        cout<<endl; 
    } 
} 
   
int main() 
{ 
    int m;
    cout<<"Tamaño de la matriz"<<endl;
    cin>>m; 
    HilbertMatrix(m);
    return 0;

} 