#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "enigma.h"

int main(int argc, char* argv[]) {

    char* archivoEntrada = argv[1];
    char* modo = argv[2];
    char* clave1 = argv[3];
    char* clave2 = argv[4];
    char* archivoSalida = argv[5];


    FILE* entrada = fopen(archivoEntrada, "r");

    FILE* salida = fopen(archivoSalida, "w");

    char alfabeto[27];
    Enigma(alfabeto, clave1, clave2);
    procesarMensaje(entrada, salida, modo, alfabeto);

    fclose(entrada);
    fclose(salida);

    printf("Proceso completado. Archivo de salida: %s\n", archivoSalida);
    return 0;
}

