// Implementacion de KNN en Atmega2560 //
// Autor: Jose Ruben Sanchez Lopez     //
// sanchezlopezjr@gmail.com            //

#include "dataset.h"
#include "funcionesKNN.h"

#define FI 100 // filas de la base de datos
#define CO 4   // numero de caracteristicas

// variables 
/*char* clasesSt[3]; // strings con las clases
char* nomAtr[CO]; // strings con los nombres de atributos
double atributos[FI][CO]; // atributos
int clasesNo[FI]; // clases
*/
double dato[CO]; // dato a clasificar
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
    
  for(j=0; j<CO; j++){
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
    int cl = clasificaKNN((double**)atributos, clasesNo, dato, 11, FI, CO);
    Serial.println(cl);

    // tac
    actual = millis();
  
    // imprimir
    imprime(dato, cl);
    Serial.print("Tiempo: "); Serial.print(actual-previo); Serial.println(" mS");
  }
}

