#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>
using namespace std;
typedef vector<vector<float>> Matriz;
typedef vector<float> Array;

Matriz crear(int fi, int col){
    Matriz matriz;
    for(int i=0; i<fi; i++){
        Array fila(col,0);
        matriz.push_back(fila);
    }
    return matriz;
}

void mostrar(Matriz Ma){
    for(int i=0; i<Ma.size();i++){
        cout<<"\t";
        for(int j=0; j<Ma[0].size();j++){
            printf("%.2f",Ma[i][j]);
            cout<<"   ";
        }
        cout<<endl;
    }
}

Matriz hilb(int n){
    Matriz matriz2=crear(n,n);
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++)
            matriz2[i-1][j-1]=1.0/(i+j-1);
    }
    return matriz2;
}

double potencia(double valor, int exponente){
    double valorcito=1;
    for(int i=0; i<exponente; i++)
        valorcito*=valor;
    return valorcito;
}

Matriz vander(int m,int n){
    int size=n-m+1;
    Matriz matriz3=crear(size,size);
    for(int i=0, l=m; i<size; i++, l++){
        for(int j=0, k=size-1; j<size; j++, k--)
            matriz3[i][j]=potencia(l,k);
    }
    return matriz3;
}

double maximo(Array array){
    double maximo=array[0];
    for(int i=1; i<array.size(); i++){
        if(array[i]>maximo){
            maximo=array[i];
        }
    }
    return maximo;
}

Matriz inv(Matriz Ma){
    double elemento, coef;
    Array aux(Ma.size()*2,0);
    Matriz matrizInver=crear(Ma.size(),Ma.size());
    Matriz matrizTmp=crear(Ma.size(),Ma.size()*2);

    for(int i=0; i<Ma.size(); i++){
        for(int j=0; j<Ma.size(); j++){
            matrizTmp[i][j]=Ma[i][j];
        }
    }

	for(int i=0;i<Ma.size();i++){
		for(int j=Ma.size(); j<2*Ma.size() ;j++){
			if(i==(j-Ma.size()))
				matrizTmp[i][j]=1;
			else
				matrizTmp[i][j]=0;
		}
	}

    //Iteraciones
    for (int s=0; s<Ma.size(); s++){
        elemento=matrizTmp[s][s];
        if(elemento==0) elemento=0.0001;
        for (int j=0; j<2*Ma.size(); j++)
            matrizTmp[s][j]=matrizTmp[s][j]/elemento;

        for(int i=0; i<Ma.size(); i++){
            if (i==s);
            else{
                coef= matrizTmp[i][s];
                for (int j=0; j<2*Ma.size(); j++)
                    aux[j]=matrizTmp[s][j]*(coef*-1);
                for (int j=0; j<2*Ma.size(); j++)
                    matrizTmp[i][j]=matrizTmp[i][j]+aux[j];
            }
        }
    }

    for(int i=0; i<Ma.size(); i++){
        for(int j=Ma.size();j<Ma.size()*2;j++){
            matrizInver[i][j-Ma.size()]=matrizTmp[i][j];
        }
    }
    return matrizInver;
}

double absoluto(double valor){
    if(valor<0)
        valor=valor*(-1);
    return valor;
}

//PRIMERA NORMA
double PrimeraNorma(Matriz Ma){
    Array arraySumas(Ma.size(),0);

    for(int j=0; j<Ma.size(); j++){
        double acum=0;
        for(int i=0; i<Ma.size(); i++){
            acum=acum+absoluto(Ma[i][j]);
        }
        arraySumas[j]=acum;
    }
    return maximo(arraySumas);
}

//TERCERA NORMA
double NormaInfinita(Matriz Ma){
    Array arraySumas(Ma.size(),0);

    for(int i=0; i<Ma.size(); i++){
        double acum=0;
        for(int j=0; j<Ma.size(); j++){
            acum=acum+absoluto(Ma[i][j]);
        }
        arraySumas[i]=acum;
    }
    return maximo(arraySumas);
}

double norm(Matriz Ma, int tipoNorma){
    double respuesta;
    if(tipoNorma==1){
        respuesta=PrimeraNorma(Ma);
        cout<<respuesta;
        return respuesta;
    }
    else if(tipoNorma==0){
        respuesta=NormaInfinita(Ma);
        cout<<respuesta;
        return respuesta;
    }
}

void cond(Matriz Ma, int tipoNorma){
    if(tipoNorma==1){
        cout<<PrimeraNorma(Ma)*PrimeraNorma(inv(Ma));
    }else if(tipoNorma==0){
        cout<<NormaInfinita(Ma)*NormaInfinita(inv(Ma));
    }else
        cout<<"Ingrese un tipo de norma valido"<<endl;
}

/*-----------------------IMPORTANTE LEER---------------------
FUNCIONES:
-NORMA => norm(matriz, tipo_norma)
    tipo_norma :
        * 0 = norma de tipo infinito
       	* 1 = norma de tipo 1
    recibe  : matriz y el tipo de norma
    retorna : escalar valor de la norma seleccionada
-CONDICIONAL => cond(matriz, tipo_norma)
    tipo_norma :
        * 0 = norma de tipo infinito
       	* 1 = norma de tipo 1
    recibe  : matriz y el tipo de norma
    retorna : numero de condiciones de la matriz
-MATRIZ DE HILBERT => hilb(tamano)
    recibe  : tamano para la matriz
    retorna : matriz de hilbert
-MATRIZ DE VANDERMONDE => vander(inicio,fin)
    inicio  : intervalo inicial
    fin     : intervalo final
    recibe  : intervalo de valores
    retorna : matriz de vandermonde
-MOSTRAR UNA MATRIZ => mostrar(matriz)
    recibe  : matriz
    retorna : imprime la matriz en consola
-------------------------------------------------------------*/

int main(){

    cout<<"\nMATRIZ HILBERT"<<endl;
    mostrar(hilb(7));
    cout<<"\nCONDICIONAL DE HILBER"<<endl;
    cout<<"\nNorma Uno: "; cond(hilb(7),0);
    cout<<"\nNorma infinito: "; cond(hilb(7),0);

    cout<<"\n\nMATRIZ VANDERMONDE"<<endl;
    mostrar(vander(1,6));
    cout<<"\nCONDICIONAL DE VANDERMONDE"<<endl;
    cout<<"\nNorma Uno: "; cond(vander(1,6),1);
    cout<<"\nNorma Infinito: "; cond(vander(1,6),0);
    cout<<endl;
    return 0;
}
