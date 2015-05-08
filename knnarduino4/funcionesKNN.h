/*----------------------------------------------------------------------------------------
funciones para el computo del algoritmo KNN / functions for the computation algorithm KNN
------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------
calculo de distancia euclidiana entre dos puntos / calculating Euclidean distance between two points
-----------------------------------------------------------------------------------------------------*/
double distanciaEuclidiana(double pt1[], double pt2[], int co);

/*-------------------------------------------------------------------------------------------------------------------------------------
calculo de distancia euclidiana entre un punto y la base de datos / calculation of Euclidean distance between a point and the database
---------------------------------------------------------------------------------------------------------------------------------------*/
void todasDistEuclid(double pt1[], double aux[], double *atributos, int fi, int co);

/*---------------------------------------------------------------------------------------------------------------
Ordenamiento de las distancias de menor a mayor conservando clase / Sorting distances Ascending preserving class
----------------------------------------------------------------------------------------------------------------*/
void ordena(double datos[], int clases[], int clasesNo[], int fi);

/*----------------------------------------------------------------
Extraer los N primeros / Extracting the first N
----------------------------------------------------------------*/
void extraeKPrimeros(double datos[], double kPrimeros[], int clases[], 
                     int kClases[], int k);
                     
/*------------------------------------------------------------------------------
Calcula la clase mas frecuente: Moda / Calculate the most common type: Fashion
------------------------------------------------------------------------------*/
int claseMasFrecuente(int clases[], int k);

/*-----------------------------------------------------------------------------------
Mapea una clase en valor entero a un string / Maps a class integer value to a string
-------------------------------------------------------------------------------------*/  
char* obtieneClaseString(int claseint);

/*-------------------------------------------------------------------------------------------------------------
Calcula la clase de un conjunto de atributos usando KNN / Calculate the class of a set of attributes using KNN
---------------------------------------------------------------------------------------------------------------*/
int clasificaKNN(double *datos, int clasesNum[], double dato[], int k, int fi, int co);

                     

