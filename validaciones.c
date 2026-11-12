#include "validaciones.h"

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* fgets evita que una letra deje la entrada bloqueada (problema de scanf). */
static int leer_linea(char linea[], size_t capacidad, const char *mensaje) {
    int c;
    size_t largo;

    for (;;) {
        printf("%s", mensaje);
        fflush(stdout);

        if (fgets(linea, (int)capacidad, stdin) == NULL) {
            return 0;  /* EOF: no seguir preguntando eternamente */
        }

        largo = strlen(linea);
        if (largo > 0 && linea[largo - 1] == '\n') {
            linea[largo - 1] = '\0';
            return 1;
        }
        if (feof(stdin)) {
            return 1;
        }

        while ((c = getchar()) != '\n' && c != EOF) { }
        puts("Error: entrada demasiado larga. Intente otra vez.");
        if (c == EOF) return 0;
    }
}

static int texto_terminado(const char *p) {
    while (isspace((unsigned char)*p)) p++;
    return *p == '\0';
}

int leer_entero_rango(const char *mensaje, int minimo, int maximo, int *valor) {
    char linea[128];
    char *fin;
    long numero;

    while (leer_linea(linea, sizeof linea, mensaje)) {
        errno = 0;
        numero = strtol(linea, &fin, 10);
        if (fin == linea || !texto_terminado(fin) || errno == ERANGE ||
            numero < INT_MIN || numero > INT_MAX) {
            puts("Error: ingrese un numero entero valido, sin letras.");
        } else if (numero < minimo || numero > maximo) {
            printf("Error: el valor permitido esta entre %d y %d.\n", minimo, maximo);
        } else {
            *valor = (int)numero;
            return 1;
        }
    }
    return 0;
}

int leer_real_rango(const char *mensaje, double minimo, double maximo, double *valor) {
    char linea[128];
    char *fin;
    double numero;
    size_t i;

    while (leer_linea(linea, sizeof linea, mensaje)) {
        /* 10900.5 o 10900,5, pero sin separador de miles. */
        for (i = 0; linea[i] != '\0'; i++) {
            if (linea[i] == ',') linea[i] = '.';
        }
        errno = 0;
        numero = strtod(linea, &fin);
        if (fin == linea || !texto_terminado(fin) || errno == ERANGE || !isfinite(numero)) {
            puts("Error: ingrese un numero real valido, sin letras ni miles separados.");
        } else if (numero < minimo || numero > maximo) {
            printf("Error: el valor permitido esta entre %.0f y %.0f.\n", minimo, maximo);
        } else {
            *valor = numero;
            return 1;
        }
    }
    return 0;
}