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

