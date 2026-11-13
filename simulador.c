#include "simulador.h"
#include "validaciones.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* x = distancia desde el centro terrestre, sobre una recta Tierra-Luna. */
static double calcular_aceleracion(double x) {
    double atraccion_tierra = G * MASA_TIERRA / (x * x);
    double atraccion_luna = G * MASA_LUNA / ((DISTANCIA_TL - x) * (DISTANCIA_TL - x));
    return -atraccion_tierra + atraccion_luna;
}

static double energia_potencial_especifica(double x) {
    return -G * MASA_TIERRA / x - G * MASA_LUNA / (DISTANCIA_TL - x);
}

static void calcular_energias(double x, double v, double masa,
                             double *ec, double *ep, double *em) {
    *ec = 0.5 * masa * v * v;
    *ep = masa * energia_potencial_especifica(x);
    *em = *ec + *ep;
}