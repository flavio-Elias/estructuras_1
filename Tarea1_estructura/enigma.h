#ifndef ENIGMA_H
#define ENIGMA_H

#include <stdio.h>

int clavesValidas(const char* clave1, const char* clave2);
int modoValido(const char* modo);
void Enigma(char alfabeto[], const char* clave1, const char* clave2);
void procesarMensaje(FILE* entrada, FILE* salida, const char* modo, const char alfabeto[]);

#endif
