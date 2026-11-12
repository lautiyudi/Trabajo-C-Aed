#ifndef SIMULADOR_H
#define SIMULADOR_H

/* Todas las longitudes fisicas se expresan en metros. */
#define G 6.674e-11                 /* N m^2 / kg^2 */
#define MASA_TIERRA 5.972e24       /* kg */
#define MASA_LUNA 7.35e22         /* kg */
#define RADIO_TIERRA 6371000.0    /* m */
#define RADIO_LUNA 1737000.0      /* m */
#define DISTANCIA_TL 384000000.0  /* m */
#define GRAVEDAD_SUPERFICIE 9.80  /* m/s^2 */
#define L1_APROX 326030000.0      /* m, valor orientativo */

#define PASO_FISICO 0.1            /* segundos por iteracion de Euler-Cromer */
#define TIEMPO_MAXIMO 864000.0     /* 10 dias, en segundos */
#define MAX_EVENTOS 4

typedef struct {
    double velocidad_inicial;  /* m/s */
    double masa_nave;          /* kg */
    double altura_km;          /* km, ingresada por el usuario */
    int intervalo_muestras;    /* segundos entre filas del historial */
    int cargados;
} DatosEntrada;

/* Lista simplemente enlazada: cada nodo conserva una muestra. */
typedef struct Nodo {
    double tiempo;
    double dist_tierra;
    double velocidad;
    double energia_c;
    double energia_p;
    double energia_m;
    struct Nodo *prox;
} Nodo;

/* Arreglo de eventos importantes (distinto del historial). */
typedef struct {
    const char *nombre;
    double tiempo;
    double posicion;
    double velocidad;
} Evento;

typedef enum {
    SIN_SIMULACION,
    LLEGADA_LUNAR,
    VELOCIDAD_AGOTADA,
    LIMITE_DE_TIEMPO
} MotivoFinal;

typedef struct {
    Nodo *prim;
    Nodo *ult;
    int cant_muestras;
    Evento eventos[MAX_EVENTOS];
    int cant_eventos;
    MotivoFinal motivo;
    int realizada;
} Simulacion;

/* Funciones publicas del simulador. */
int cargar_datos(DatosEntrada *datos);
void mostrar_constantes(void);
int ejecutar_simulacion(const DatosEntrada *datos, Simulacion *sim);
void mostrar_resultados(const DatosEntrada *datos, const Simulacion *sim);
void liberar_historia(Simulacion *sim);

#endif
