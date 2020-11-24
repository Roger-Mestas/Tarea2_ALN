#include <iostream>
#include <cmath>
double norm2(int a, int b){
    double result = 0;
    result = sqrt(pow(a,2) + pow(b,2));
    return result;
}
int main(){
    int numeros[100][100],filas,columnas;
    std::cout << "#f:"; std::cin >> filas;
    std::cout << "#c:"; std::cin >> columnas;

    for (int i = 0 ; i < filas ; i++){
        for(int j = 0 ; j < columnas ; j++){ 
            std::cout << "#" ; std::cin >> numeros[i][j]; 
        }
    }

    for (int i = 0 ; i < filas ; i++){
        for (int j = 0 ; j < columnas ; j++)
            std::cout << numeros[i][j] <<  "   " ;
        std::cout << std::endl;
    }

    int c = 0; // usando la norma 0 
    for (int i = 0 ; i < filas ; i++){
        for (int j = 0 ; j < columnas ; j++)
            if(numeros[i][j] != 0)
                c++;      
    }

    std::cout << "Norma 0:" << c << std::endl;

    int count = 0; // usando la norma 1
    for (int i = 0 ; i < filas ; i++){
        for (int j = 0 ; j < columnas ; j++)
            count += abs(numeros[i][j]);
    }
    std::cout << "Norma 1:" << count << std::endl;

    std::cout << "Traspuesta:" << std::endl;
    int numeros1[100][100];
    for (int i = 0 ; i < filas ; i++){
        for(int j = 0 ; j < columnas ; j++){  
            numeros1[i][j] = numeros[j][i]; 
        }
    }

    for (int i = 0 ; i < filas ; i++){
        for (int j = 0 ; j < columnas ; j++)
            std::cout << numeros1[i][j] <<  "   " ;
        std::cout << std::endl;
    }

    double max = 0;
    double nor = 0;
    for (int i = 0 ; i < filas ; i++){
        for(int j = 0 ; j < columnas ; j++){ 
            nor = norm2(numeros1[i][j],numeros[i][j]);
            if(nor >= max)
                max = nor;
        }
    }

    std::cout << "norm2:" << max << std::endl;
    return 0;
}