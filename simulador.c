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

static double posicion_equilibrio(void) {
    /* |gT| = |gL|, NO es el punto L1. */
    return DISTANCIA_TL / (1.0 + sqrt(MASA_LUNA / MASA_TIERRA));
}

/* Mapa ASCII: T = Tierra, O = Orion, L = Luna. No usa graficos. */
static void dibujar_ascii(double tiempo, double x) {
    enum { ANCHO = 53 };
    char linea[ANCHO + 1];
    int i;
    int posicion = (int)lround(x / DISTANCIA_TL * (ANCHO - 1));

    if (posicion < 1) posicion = 1;
    if (posicion > ANCHO - 2) posicion = ANCHO - 2;

    for (i = 0; i < ANCHO; i++) linea[i] = '-';
    linea[0] = 'T';
    linea[ANCHO - 1] = 'L';
    linea[posicion] = 'O';
    linea[ANCHO] = '\0';

    printf("%7.2f h | %s | %9.0f km\n", tiempo / 3600.0, linea, x / 1000.0);
}

void liberar_historia(Simulacion *sim) {
    Nodo *p = sim->prim;
    while (p != NULL) {
        Nodo *siguiente = p->prox;
        free(p);
        p = siguiente;
    }
    sim->prim = NULL;
    sim->ult = NULL;
    sim->cant_muestras = 0;
    sim->cant_eventos = 0;
    sim->motivo = SIN_SIMULACION;
    sim->realizada = 0;
}

int cargar_datos(DatosEntrada *datos) {
    DatosEntrada nuevos = {0};

    puts("\n--- DATOS INICIALES DE ORION ---");
    puts("Referencia: 10900 m/s, 26000 kg y 192 km de altura.");
    puts("Use numeros sin separador de miles. Ejemplo: 10900.5");
    puts("Los intervalos son limites de este simulador, no leyes fisicas.");

    if (!leer_real_rango("Velocidad inicial (10500 a 11500 m/s): ",
                         10500, 11500, &nuevos.velocidad_inicial)) return 0;
    if (!leer_real_rango("Masa de la nave (5000 a 50000 kg): ",
                         5000, 50000, &nuevos.masa_nave)) return 0;
    if (!leer_real_rango("Altura de orbita (180 a 1000 km): ",
                         180, 1000, &nuevos.altura_km)) return 0;
    if (!leer_entero_rango("Intervalo para guardar muestras (13900 a 40000 s): ",
                           13900, 40000, &nuevos.intervalo_muestras)) return 0;

    nuevos.cargados = 1;
    *datos = nuevos;
    puts("Datos cargados. Puede ejecutar la simulacion (opcion 3).");
    return 1;
}

