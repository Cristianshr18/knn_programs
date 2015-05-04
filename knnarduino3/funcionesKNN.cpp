#include <HardwareSerial.h> // solo para Debug

/*------------------------------------------ 
funciones para el computo del algoritmo KNN
--------------------------------------------*/
//#include "dataset.h"
#include "funcionesKNN.h"

#include <math.h>

/*----------------------------------------------
calculo de distancia euclidiana entre dos puntos
------------------------------------------------*/
double distanciaEuclidiana(double pt1[], double pt2[], int co){  
  int i;
  double suma = 0;
  for(i=0; i<co; i++){
    suma = pow(pt1[i] - pt2[i], 2) + suma;
  }
  return sqrt(suma);
}


/*---------------------------------------------------------------
calculo de distancia euclidiana entre un punto y la base de datos
----------------------------------------------------------------*/
void todasDistEuclid(double pt1[], double aux[], double *atributos, int fi, int co){
  int i = 0, j = 0;
  double pt2[co];
  
  for(i = 0; i<fi; i++){
    for(j=0; j<co; j++){           
      pt2[j] = atributos[i*co+j];
    }
    
    aux[i] = distanciaEuclidiana(pt1, pt2, co);
  }
}

/*----------------------------------------------------------------
Ordenamiento de las distancias de menor a mayor
----------------------------------------------------------------*/
void ordena(double datos[], int clases[], int clasesNo[], int fi){
  int i =1, j = 1, f = 1, temp[2];
  
  //crear una copia de las clases originales
  for(i=0; i<fi; i++){
    clases[i] = clasesNo[i];  
  }
  
  // ordenar
  for(i=1; (i<=fi)&&f; i++){
    f = 0;
    for(j=0; j<(fi-1); j++){
      if(datos[j+1] < datos[j]){ // orden descendente >, ascendente <
        temp[0] = datos[j];    temp[1] = clases[j];
        datos[j] = datos[j+1]; clases[j] = clases[j+1]; 
        datos[j+1] = temp[0];  clases[j+1] = temp[1];
        f = 1;
      }
    }
  }
}

/*----------------------------------------------------------------
Extraer los N primeros
----------------------------------------------------------------*/
void extraeKPrimeros(double datos[], double kPrimeros[], int clases[], 
                     int kClases[], int k){
 
  for(int i=0; i<k; i++){
    kPrimeros[i] = datos[i];  
    kClases[i] = clases[i];
  }
}

/*----------------------------------------------------------------
Calcula la clase mas frecuente: Moda
----------------------------------------------------------------*/
int claseMasFrecuente(int clases[], int k){
  
  int cont = 0, cont2 = 0, pos = 0, num = 0, i = 0;
  int frec[k], mayor = 0, posmayor = 0, aux[k];
  
  // inicializar el contador de frecuencias
  for(i=0; i<k; i++){
    frec[k] = 0;  
  }

  // comprobar las repeticiones de cada numero
  for(cont=0; cont<k; cont++){
    num = clases[cont];
    pos = cont;
    
    for(cont2 = 0; cont2<k; cont2++){
      if(clases[cont2] == num){
        aux[pos]++;
      }  
    }
  }
   
  mayor =aux[0];
  posmayor = 0;
    
  for(cont=0; cont<k; cont++){
    if(aux[cont] > mayor){
      posmayor = cont;
      mayor = aux[cont];
    }  
  }
  
  return clases[posmayor];
}

  
/*----------------------------------------------------------------
Calcula la clase de un conjunto de atributos usando KNN
----------------------------------------------------------------*/
int clasificaKNN(double *datos, int clasesNum[], double dato[], int k, int fi, int co){
  double aux2[fi], kPrimeros[k];
  int clases[fi];
  int kClases[k];
  
  todasDistEuclid(dato, aux2, (double*)datos, fi, co); 
  ordena(aux2, clases, clasesNum, fi); 
  extraeKPrimeros(aux2, kPrimeros, clases, kClases, k); 
  
  // calculo de la moda
  int cont = 0, cont2 = 0, pos = 0, num = 0, i = 0;
  int frec[k], mayor = 0, posmayor = 0, aux[k];
  
  // inicializar el contador de frecuencias
  for(i=0; i<k; i++){
    frec[k] = 0;  
  }
 
  // comprobar las repeticiones de cada numero
  for(cont=0; cont<k; cont++){
    num = clases[cont];
    pos = cont;
    
    for(cont2 = 0; cont2<k; cont2++){
      if(clases[cont2] == num){
        aux[pos]++;
      }  
    }
  }
   
  mayor =aux[0];
  posmayor = 0;
    
  for(cont=0; cont<k; cont++){
    if(aux[cont] > mayor){
      posmayor = cont;
      mayor = aux[cont];
    }  
  }
  
  return clases[posmayor];
}


