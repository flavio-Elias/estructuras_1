#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "enigma.h"

#define ALPHABET_LEN 26

int tieneLetrasRepetidas(const char* palabra) {
    int letras[ALPHABET_LEN] = {0};
    for (int i = 0; palabra[i] != '\0'; i++) {
        char c = tolower(palabra[i]);
        if (!isalpha(c)) return 1;
        int index = c - 'a';
        if (letras[index]) return 1;
        letras[index] = 1;
    }
    return 0;
}

int clavesValidas(const char* clave1, const char* clave2) {
    if (tieneLetrasRepetidas(clave1) || tieneLetrasRepetidas(clave2))
        return 0;

    int letras[ALPHABET_LEN] = {0};
    for (int i = 0; clave1[i] != '\0'; i++)
        letras[tolower(clave1[i]) - 'a'] = 1;
    for (int i = 0; clave2[i] != '\0'; i++)
        if (letras[tolower(clave2[i]) - 'a']) return 0;

    return 1;
}

int modoValido(const char* modo) {
    return strcmp(modo, "encode") == 0 || strcmp(modo, "decode") == 0;
}

void crearAlfabeto(char alfabeto[], const char* clave1, const char* clave2) {
    int usado[ALPHABET_LEN] = {0};
    int i = 0;

    for (int j = 0; clave1[j] != '\0'; j++) {
        char c = tolower(clave1[j]);
        if (!usado[c - 'a']) {
            alfabeto[i++] = c;
            usado[c - 'a'] = 1;
        }
    }

    for (int j = 0; clave2[j] != '\0'; j++) {
        char c = tolower(clave2[j]);
        if (!usado[c - 'a']) {
            alfabeto[i++] = c;
            usado[c - 'a'] = 1;
        }
    }

    for (char c = 'a'; c <= 'z'; c++) {
        if (!usado[c - 'a']) {
            alfabeto[i++] = c;
        }
    }

    alfabeto[ALPHABET_LEN] = '\0';
}

void procesarMensaje(FILE* entrada, FILE* salida, const char* modo, const char alfabeto[]) {
    char c;
    while ((c = fgetc(entrada)) != EOF) {
        if (isalpha(c)) {
            int index;
            if (strcmp(modo, "encode") == 0) {
                index = tolower(c) - 'a';
                c = isupper(c) ? toupper(alfabeto[index]) : alfabeto[index];
            } else {
                for (index = 0; index < ALPHABET_LEN; index++) {
                    if (alfabeto[index] == tolower(c)) break;
                }
                c = isupper(c) ? toupper('a' + index) : 'a' + index;
            }
        }
        fputc(c, salida);
    }
}
