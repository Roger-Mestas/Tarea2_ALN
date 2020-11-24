#include <iostream>  
void hilbert(int n){ 
    float H[n][n]; 
    for (int i = 0; i < n; i++) { 
        for (int j = 0; j < n; j++) {  
            H[i][j] = (float)1.0/((i + 1)+(j + 1) -1.0); 
        } 
    } 
    for (int i = 0; i < n; i++) { 
        for (int j = 0; j < n; j++)  
            std::cout << H[i][j] << " ";         
        std::cout << std::endl; 
    } 
} 

int main(){ 
    int n;
    std::cout << "número de matriz:"; std::cin >> n; 
    hilbert(n); 
    return 0; 
} 