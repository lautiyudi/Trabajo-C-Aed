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
/* Insertar al final de la lista, como en el pseudocodigo del equipo. */
static int guardar_historia(Simulacion *sim, double tiempo, double x,
                           double v, double masa) {
    Nodo *p = malloc(sizeof *p);
    if (p == NULL) return 0;

    p->tiempo = tiempo;
    p->dist_tierra = x;
    p->velocidad = v;
    calcular_energias(x, v, masa, &p->energia_c, &p->energia_p, &p->energia_m);
    p->prox = NULL;

    if (sim->prim == NULL) {
        sim->prim = p;
    } else {
        sim->ult->prox = p;
    }
    sim->ult = p;
    sim->cant_muestras++;
    return 1;
}

/* El arreglo guarda hitos, mientras que la lista guarda muestras periodicas. */
static void guardar_evento(Simulacion *sim, const char *nombre,
                          double tiempo, double x, double v) {
    if (sim->cant_eventos < MAX_EVENTOS) {
        Evento *e = &sim->eventos[sim->cant_eventos];
        e->nombre = nombre;
        e->tiempo = tiempo;
        e->posicion = x;
        e->velocidad = v;
        sim->cant_eventos++;
    }
}