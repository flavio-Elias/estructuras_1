#ifndef ENIGMA_H
#define ENIGMA_H

#include <stdio.h>

extern const char* alfabeto_con_caracteres;
int clavesValidas(const char* clave1, const char* clave2);
int modoValido(const char* modo);
void Enigma(char alfabeto[], const char* clave1, const char* clave2, const char* alfabeto_con_caracteres);
void procesarMensaje(FILE* archivo_de_entrada, FILE* archivo_de_salida, const char* modo, const char* alfabeto_con_caracteres, const char* cifrado);

#endif
