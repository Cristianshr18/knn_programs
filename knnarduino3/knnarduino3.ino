// Implementacion de KNN en Atmega2560 //
// Autor: Jose Ruben Sanchez Lopez     //
// sanchezlopezjr@gmail.com            //

#include "dataset.h"
#include "funcionesKNN.h"
#include "prueba.h"

double dato[co];
long actual = 0, previo = 0;

//-----------------------------------------------------------------------
// Extrae caracteres dados los identificadores y los convierte a double
//-----------------------------------------------------------------------
void extraeDatos(String str, double dato[], char dlm[]){
  
  String auxstr = "";
  int posdlm[5], tamstr = 0;
  int i= 0, j = 0;
  
  // buscar caracteres de identificacion
  posdlm[0] = str.indexOf(dlm[0]); // (
  posdlm[1] = str.indexOf(dlm[1]); // ,
  posdlm[2] = str.indexOf(dlm[1], posdlm[1] + 1); // ,
  posdlm[3] = str.indexOf(dlm[1], posdlm[2] + 1); // ,
  posdlm[4] = str.indexOf(dlm[2]); // )
    
  for(j=0; j<co; j++){
    // extraer datos numericos
    for(i=posdlm[j]+1; i<posdlm[j+1]; i++){
      auxstr = auxstr + str[i];  
    }

    //convertir a double
    int y = auxstr.length();
    char buf[y+1];
    auxstr.toCharArray(buf, y+1);
    dato[j] = atof(buf);
    
    //Serial.println(dato[j],3);
    auxstr=""; // reset del auxiliar
    }      
}

//-----------------------------------------------------------------------
// Impresion de confirmacion
//-----------------------------------------------------------------------
void imprime(double dato[], int clase){
  
  Serial.println("-----------------------------------------------");
  Serial.print(nomAtr[0]); Serial.print(": "); Serial.print(dato[0],3); Serial.println(" cms");
  Serial.print(nomAtr[1]); Serial.print(": "); Serial.print(dato[1],3); Serial.println(" cms");
  Serial.print(nomAtr[2]); Serial.print(": "); Serial.print(dato[2],3); Serial.println(" cms");
  Serial.print(nomAtr[3]); Serial.print(": "); Serial.print(dato[3],3); Serial.println(" cms");
  Serial.print(" >> Clase: "); Serial.println(clasesSt[clase]);
}

//-----------------------------------------------------------------------
// Calcula la exactitud del algoritmo KNN dada una k
//-----------------------------------------------------------------------
double calculaExactitud(int k){
  int i, j, cl;
  int buenos = 0, malos = 0;
  double exactitud = 0;
  double dato2[co];
  
  for(i=0; i<fi2; i++){
    for(j=0; j<co2; j++){
      // extraer un dato de prueba.h
      dato2[j] = atributos2[i][j];
    }  
    // clasificarlo
    cl = clasificaKNN((double*)atributos, clasesNo, dato, k, fi, co);
    
    // comparar la clase 
    if(cl == clasesNo2[i]){
      buenos = buenos + 1;  
    }
    
    else{
      malos = malos + 1;  
    }
  }
  
  exactitud = buenos/fi2;
  
  Serial.print("k = "); Serial.print(k); Serial.print("--  Exactitud = "); Serial.println(exactitud, 3);
  
  return exactitud;
  
}

//-----------------------------------------------------------------------
// Configuracion del microcontrolador
//-----------------------------------------------------------------------
void setup() {
  Serial.begin(9600);
  delay(1000);
  Serial.println("===============================================");
  Serial.println("===         Clasificacion con KKN           ===");
  Serial.println("===============================================");
  delay(500);
}

//-----------------------------------------------------------------------
// Programa principal
//-----------------------------------------------------------------------
void loop() {
  
  // recibir los datos a clasificar
  if(Serial.available()){       
   
    // recibir una cadena hasta que se tenga el '\n'
    String str = Serial.readStringUntil('\n');  
    extraeDatos(str, dato, "{,}");
    
    // tic
    previo = millis();    
          
    // encontrar la clase, con 5 vecinos cercanos
    int cl = clasificaKNN((double*)atributos, clasesNo, dato, 11, fi, co);

    // tac
    actual = millis();
  
    // imprimir
    //imprime(dato, cl);
    Serial.print("Tiempo: "); Serial.print(actual-previo); Serial.println(" mS");   
  }
}


