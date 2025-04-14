#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "enigma.h"

#define largo_del_abecedario 26

//definimos la funcion que verifica si los caracteres son todos distintos para las dos palabras
int tieneLetrasRepetidas(const char* palabra) {

  //se crea un arreglo con 26 coordenadas, todas comenzadas de 0, por ejemplo (0,0,0,0,...,0)
    int letras[largo_del_abecedario] = {0};
    //se recorre la palabra letra por letra hasta que termine ( \0 es el indicador de que termino el arreglo, me lo dijo chatgpt)
    for (int i = 0; palabra[i] != '\0'; i++) {

     	//guardamos la letra que recorremos en una variable
        char c = palabra[i];

        //verificamos que la letra sea una letra osea que no fuese un caracter ya sean espacios o caracteres como !"#$ (esta funcion me la dio el chatgpt)
        if (!isalpha(c)) return 1;

        //asignamos a cada letra un espacio en el arreglo, ademas en caso de que este "contador" llegue a 2 devuelve verdader y falla
        int index = c - 'a';
        if (letras[index]) return 1;
        letras[index] = 1;
    }
    return 0;
}

//Recibe 2 palabras y verficia si son (o no) validas las palabras
int clavesValidas(const char* palabra1, const char* palabra2) {

  // Verifica que cada palabra no tenga letras repetidas
    if (tieneLetrasRepetidas(palabra1) || tieneLetrasRepetidas(palabra2))
        return 0;

  //volvemos a crear el arreglo de 26 coordenadas para almacenar si se han o no repetido las letras
    int letras[largo_del_abecedario] = {0};

    //añade 1 si hay x letra definida
    for (int i = 0; palabra1[i] != '\0'; i++)
        letras[tolower(palabra1[i]) - 'a'] = 1;

    //verifica si esas letras que encontramos en la primera parte se vuelven a repetir (esto se verifica en el if)
    for (int i = 0; palabra2[i] != '\0'; i++)
        if (letras[tolower(palabra2[i]) - 'a']) return 0;

    return 1;
}

//esta funcion verifica si se ingreso bien o no el parametro para codificar o decodificar
int modos(const char* modo) {
    return strcmp(modo, "encode") == 0 || strcmp(modo, "decode") == 0;
}

//se crea el alfabeto alternativo que utiliza el codigo enigma
void Enigma(char alfabeto[], const char* palabra1, const char* palabra2) {
  //guarda aquellas letras que ya fueron usadas
  int usado[largo_del_abecedario] = {0};
	//indice para recorrer este alfabeto
  int i = 0;

  //se recorre la palabra 1
    for (int j = 0; palabra1[j] != '\0'; j++) {
      //convierte la letra recorrida a una minsucula
        char c = tolower(palabra1[j]);

        //le asignamos una posicion en el alfabeto
        usado[c - 'a'] = 1;
        alfabeto[i++] = c;

    }

    //repetimos lo mismo para la segunda palabra
    for (int j = 0; palabra2[j] != '\0'; j++) {
        char c = tolower(palabra2[j]);
        usado[c - 'a'] = 1;
        alfabeto[i++] = c;

    }

    //rellenamos el resto del abecedario (es decir rellenamos las letras que no usamos)
    for (char c = 'a'; c <= 'z'; c++) {
        if (!usado[c - 'a']) {
            alfabeto[i++] = c;
        }
    }

    //maracmaos el fin del abecedario
    alfabeto[largo_del_abecedario] = '\0';
}

//funcion que lee, codifica y entrega el mensaje de salida
void procesarMensaje(FILE* archivo_de_entrada, FILE* archivo_de_salida, const char* modo, const char alfabeto[]) {

  //leemos el archivo hasta que termina (EOF= End Of File)
  char c;
    while ((c = fgetc(archivo_de_entrada)) != EOF) {

      //Nos aseguramos que en el archivo solo modifiquemos las letras, no podemos modificar los numeros ya que no lo hicimos antes y el programa no admite numeros
        if (isalpha(c)) {

          //declaramos un indice
            int indice;

            //hacemos la distincion si se esta codificando (encode) o decodificando (decode)
            if (strcmp(modo, "encode") == 0) {
              //convertimos la letra a minuscula y le asignamos un indice
                indice = tolower(c) - 'a';

                //si la letra ingresada es mayuscula entonces devolvemos esa letra a mayuscula
                if (isupper(c)) {
    				c = toupper(alfabeto[indice]);
				}else {
                     c=alfabeto[indice];
				}
            //en caso de que no sea encode, es decir, decode hacemos lo mismo
            } else {

              //Buscamos la letra en el abecedario que hicmos
                for (indice = 0; indice < largo_del_abecedario; indice++) {
    				if (alfabeto[indice] == tolower(c)) break;
				}

                //vemos si la letra original era mayuscula, en caso de que fuese le devolvemos a ese estado
				if (isupper(c)) {
    				c = toupper('a' + indice);
				} else {
    				c = 'a' + indice;
                }
			}

        }
        //escribimos la letra resultante en el archivo
        fputc(c, archivo_de_salida);
    }
}
