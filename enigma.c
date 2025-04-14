#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "enigma.h"

const char* alfabeto_con_caracteres = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%&()[]{}=+-_.,:;?<> ";

//definimos la funcion que verifica si los caracteres son todos distintos para las dos palabras
int tieneLetrasRepetidas(const char* palabra) {
   //Vector para guardar los caracteres
	int usado[256]={0};

    //se recorre la palabra letra por letra hasta que termine ( \0 es el indicador de que termino el arreglo, me lo dijo chatgpt)
    for (int i = 0; palabra[i] != '\0'; i++) {

     	//guardamos la letra que recorremos en una variable
        unsigned char c = palabra[i];

        //anota caracteres repetidos
        if (!usado[c]) return 1;
		usado[c]=1;

    }
    return 0;
}

//Recibe 2 palabras y verficia si son (o no) validas las palabras
int clavesValidas(const char* palabra1, const char* palabra2) {

  // Verifica que cada palabra no tenga letras repetidas
    if (tieneLetrasRepetidas(palabra1) || tieneLetrasRepetidas(palabra2))
        return 0;

   //Vector para guardar los caracteres
    int usado[256] = {0};

    //añade 1 si hay x letra definida
    for (int i = 0; palabra1[i] != '\0'; i++){
        unsigned char c=palabra1[1];
    	usado[c] =1;
    }

    //verifica si esas letras que encontramos en la primera parte se vuelven a repetir (esto se verifica en el if)
    for (int i = 0; palabra2[i] != '\0'; i++){
        unsigned char c=palabra2[i];
    	if(usado[c]) return 0;
    }

    return 1;
}

//esta funcion verifica si se ingreso bien o no el parametro para codificar o decodificar
int modos(const char* modo) {
    return strcmp(modo, "encode") == 0 || strcmp(modo, "decode") == 0;
}

//se crea el alfabeto alternativo que utiliza el codigo enigma
void Enigma(char alfabeto_cifrado[], const char* palabra1, const char* palabra2, const char* alfabeto) {
  //guarda aquellas letras que ya fueron usadas
  int usado[256] = {0};
	//indice para recorrer este alfabeto
  int i = 0;

  //se recorre la palabra 1
    for (int j = 0; palabra1[j] != '\0'; j++) {
      //convierte la letra recorrida a una minsucula
        unsigned char c = palabra1[j];

        if(!usado[c]){
          alfabeto_cifrado[i++] =c;
          usado[c]=1;
		}
    }

    //repetimos lo mismo para la segunda palabra
    for (int j = 0; palabra2[j] != '\0'; j++) {
        unsigned char c = palabra2[j];
        if(!usado[c]){
          alfabeto_cifrado[i++] =c;
          usado[c]=1;
        }


    }

    //rellenamos el resto del abecedario (es decir rellenamos las letras que no usamos)
    for (int j=0; alfabeto[j] != '\0'; j++) {
        unsigned char c=alfabeto[j];
        if(!usado[c]){
            alfabeto_cifrado[i++] =c;
            usado[c]=1;
        }
    }

    //maracmaos el fin del abecedario
    alfabeto_cifrado[i] = '\0';
}

//funcion que lee, codifica y entrega el mensaje de salida
void procesarMensaje(FILE* archivo_de_entrada, FILE* archivo_de_salida, const char* modo, const char* alfabeto, const char* cifrado ) {

  //leemos el archivo hasta que termina (EOF= End Of File)
  char c;
    while ((c = fgetc(archivo_de_entrada)) != EOF) {

    //variable que indica la posicion en nuestro abecedario
    	char* pos;

            //hacemos la distincion si se esta codificando (encode) o decodificando (decode)
            if (strcmp(modo, "encode") == 0) {
				//buscamos la posicion del caracter c en el alfabeto con caracteres
				pos= strchr(alfabeto,c);
                //linea que cifra el mensaje, verifica que este c en el alfabeto con caracteres y luego reemplaza c por el caracter correspondiente en el alfabeto cifrado
                if(pos) c =cifrado[pos - alfabeto];
			}else {
                //buscamos la posicion de c esta vez en alfabeto cifrado
            	pos = strchr(cifrado,c);

                //linea que decifra el mensaje, verificamos que c este en cifrado y luego reemplaza c en el alfabeto con caracteres
				if (pos) c =alfabeto[pos - cifrado];

        }
        //escribimos la letra resultante en el archivo
        fputc(c, archivo_de_salida);
    }
}
