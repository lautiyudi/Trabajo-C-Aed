#include <stdio.h>
#include "simulador.h"
#include "validaciones.h"

int main(void) {
    DatosEntrada datos = {0};
    Simulacion sim = {0};
    int opcion;
    int continuar = 1;

    while (continuar) {
        puts("\n===========================================");
        puts("      SIMULADOR ARTEMIS - ESCENARIO 3");
        puts("===========================================");
        puts("1. Cargar / modificar datos de entrada");
        puts("2. Mostrar constantes fisicas");
        puts("3. Ejecutar simulacion ASCII");
        puts("4. Ver resultados y analisis");
        puts("5. Salir");

        if (!leer_entero_rango("Seleccione una opcion (1-5): ", 1, 5, &opcion)) {
            puts("\nEntrada finalizada. Cerrando el programa.");
            break;
        }

        switch (opcion) {
            case 1:
                if (!cargar_datos(&datos)) {
                    puts("Entrada interrumpida. Se cierra el programa.");
                    continuar = 0;
                } else {
                    /* Los resultados anteriores ya no sirven con datos nuevos. */
                    liberar_historia(&sim);
                }
                break;
            case 2:
                mostrar_constantes();
                break;
            case 3:
                if (!datos.cargados) {
                    puts("Primero debe cargar datos con la opcion 1.");
                } else {
                    ejecutar_simulacion(&datos, &sim);
                }
                break;
            case 4:
                mostrar_resultados(&datos, &sim);
                break;
            case 5:
                puts("Gracias por utilizar el simulador Artemis.");
                continuar = 0;
                break;
        }
    }

    liberar_historia(&sim); /* Evita dejar memoria dinamica sin liberar. */
    return 0;
}
