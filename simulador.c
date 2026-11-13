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

void mostrar_constantes(void) {
    puts("\n--- CONSTANTES DEL SISTEMA ARTEMIS ---");
    printf("Gravedad superficial terrestre: %.2f m/s^2\n", GRAVEDAD_SUPERFICIE);
    printf("Gravitacion universal G:        %.3e N*m^2/kg^2\n", G);
    printf("Masa de la Tierra:             %.3e kg\n", MASA_TIERRA);
    printf("Masa de la Luna:               %.3e kg\n", MASA_LUNA);
    printf("Radio de la Tierra:            %.0f km\n", RADIO_TIERRA / 1000.0);
    printf("Distancia Tierra-Luna:         %.0f km\n", DISTANCIA_TL / 1000.0);
    printf("L1 aproximado (desde Tierra):  %.0f km\n", L1_APROX / 1000.0);
    printf("Igualdad de gravedad (modelo): %.0f km\n", posicion_equilibrio() / 1000.0);
    puts("NOTA: L1 y el punto de igualdad de gravedad NO son iguales.");
}


int ejecutar_simulacion(const DatosEntrada *datos, Simulacion *sim) {
    double tiempo = 0;
    double x = RADIO_TIERRA + datos->altura_km * 1000.0;
    double v = datos->velocidad_inicial;
    double x_eq = posicion_equilibrio();
    double t_proxima_muestra = datos->intervalo_muestras;
    double t_ultimo_guardado = 0;
    double x_anterior;

    if (!datos->cargados) {
        puts("Error: primero debe cargar los datos.");
        return 0;
    }

    liberar_historia(sim);
    puts("\n--- INYECCION TRANSLUNAR: SIMULACION ASCII ---");
    puts("T = Tierra | O = Orion | L = Luna");
    puts("Modelo 1D simplificado: Tierra y Luna fijas; motores apagados.");
    puts("El programa calcula cada 0.1 s y dibuja cada muestra solicitada.");
    puts("(La posicion en el dibujo es proporcional a la distancia.)");

    guardar_evento(sim, "Inicio TLI", tiempo, x, v);
    if (!guardar_historia(sim, tiempo, x, v, datos->masa_nave)) goto sin_memoria;
    dibujar_ascii(tiempo, x);

    while (tiempo < TIEMPO_MAXIMO && x < DISTANCIA_TL - RADIO_LUNA &&
           x > RADIO_TIERRA && v > 0) {
        double a = calcular_aceleracion(x);
        x_anterior = x;

        /* Euler-Cromer: primero velocidad, despues posicion. */
        v = v + a * PASO_FISICO;
        x = x + v * PASO_FISICO;
        tiempo = tiempo + PASO_FISICO;

        if (x >= DISTANCIA_TL - RADIO_LUNA) x = DISTANCIA_TL - RADIO_LUNA;
        if (x <= RADIO_TIERRA) x = RADIO_TIERRA;

        if (x_anterior < L1_APROX && x >= L1_APROX) {
            guardar_evento(sim, "Cruce L1 aproximado", tiempo, x, v);
        }
        if (x_anterior < x_eq && x >= x_eq) {
            guardar_evento(sim, "Igualdad de gravedad", tiempo, x, v);
        }

        if (tiempo >= t_proxima_muestra) {
            if (!guardar_historia(sim, tiempo, x, v, datos->masa_nave)) goto sin_memoria;
            dibujar_ascii(tiempo, x);
            t_ultimo_guardado = tiempo;
            t_proxima_muestra += datos->intervalo_muestras;
        }
    }

    if (tiempo > t_ultimo_guardado) {
        if (!guardar_historia(sim, tiempo, x, v, datos->masa_nave)) goto sin_memoria;
        dibujar_ascii(tiempo, x);
    }

    guardar_evento(sim, "Final de simulacion", tiempo, x, v);
    if (x >= DISTANCIA_TL - RADIO_LUNA) {
        sim->motivo = LLEGADA_LUNAR;
        puts("RESULTADO: Orion alcanzo la superficie lunar en el modelo 1D.");
    } else if (v <= 0 || x <= RADIO_TIERRA) {
        sim->motivo = VELOCIDAD_AGOTADA;
        puts("RESULTADO: Orion dejo de avanzar antes de llegar a la Luna.");
    } else {
        sim->motivo = LIMITE_DE_TIEMPO;
        puts("RESULTADO: se alcanzo el limite de 10 dias de simulacion.");
    }
    sim->realizada = 1;
    printf("Muestras guardadas en la lista: %d\n", sim->cant_muestras);
    puts("Vea la opcion 4 para consultar la tabla y el analisis.");
    return 1;

sin_memoria:
    puts("Error: no hay memoria suficiente para guardar la simulacion.");
    liberar_historia(sim);
    return 0;
}