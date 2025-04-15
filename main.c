#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "enigma.h"




int main(int argc, char* argv[]) {

    char* archivo_de_entrada = argv[1];
    char* modo = argv[2];
    char* palabra1 = argv[3];
    char* palabra2 = argv[4];
    char* archivo_de_salida = argv[5];
    
    ///FUNCIONES ERROR
    ///1
    int bruh = argc;
    if (bruh != 6){
        printf("Se ha producido un error. \nEl numero de argumentos es erroneo, debe de entregar 6 argumentos.");
        return 1;
    }

    ///2
    if (!modos(modo)) {
        printf("Se ha producido un error. \nNo se ha introducido un modo valido, los modos validos son (encode) y (decode.\n");
        return 1;
    }
    ///3
    if (strlen(palabra1) != strlen(palabra2)){
        printf("Se a producido un error. \nAmbas palabras deben tener la misma cantidad de caracteres");
        return 1;
    }

    ///4
    if (strcmp(archivo_de_entrada, archivo_de_salida) == 0) {
        printf("Se ha producido un error. \nLos archivos de entrada y salida tienen el mismo nombre (deben ser distintos).\n");
        return 1;
    }
    ///////

    FILE* entrada = fopen(archivo_de_entrada, "r");

    FILE* salida = fopen(archivo_de_salida, "w");

    char alfabeto_cifrado[256];
    Enigma(alfabeto_cifrado, palabra1, palabra2, alfabeto_con_caracteres);
    procesarMensaje(entrada, salida, modo, alfabeto_con_caracteres,alfabeto_cifrado);

    fclose(entrada);
    fclose(salida);

    printf("Proceso completado. Archivo de salida: %s\n", archivo_de_salida);
    return 0;
}

