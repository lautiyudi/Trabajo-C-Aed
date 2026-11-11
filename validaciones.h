#ifndef VALIDACIONES_H
#define VALIDACIONES_H

/* Devuelven 1 si se leyo un dato valido, 0 si finalizo la entrada. */
int leer_entero_rango(const char *mensaje, int minimo, int maximo, int *valor);
int leer_real_rango(const char *mensaje, double minimo, double maximo, double *valor);

#endif
