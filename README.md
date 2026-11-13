# TRABAJO FINAL INTEGRADOR — LABORATORIO DE C

## 1. Integrantes y comisión

*Carrera:* Ingeniería en Sistemas de Información


*Universidad:* Universidad Tecnológica Nacional — Facultad Regional Resistencia


*Materia:* Algoritmos y Estructuras de Datos


*Comisión:* 1.1 (A)


*Integrantes:*

* Iván Gabriel Bulacio Báez
* Lucas Alfonso Gurrieri Agustini
* Lucas Emanuel Monticelli
* Lautaro Amir Yudi

## 2. Descripción del proyecto

### Simulador Artemis — Escenario 3: Inyección Translunar (TLI)

El proyecto consiste en desarrollar un simulador en lenguaje C basado en la misión Artemis, específicamente en la etapa de inyección translunar de la nave Orión.

El objetivo es representar el comportamiento de la nave durante su desplazamiento desde las proximidades de la Tierra hacia la Luna, considerando la influencia de las fuerzas gravitatorias de ambos cuerpos.

Para ello, el programa utiliza conceptos de la Primera Ley de Newton, la gravitación universal y las energías cinética, potencial y mecánica.

La simulación utiliza como valores de referencia:

* Velocidad inicial: 10.900 m/s.
* Masa de la nave Orion: 26.000 kg.
* Altura orbital inicial: 192 km.
* Distancia media entre la Tierra y la Luna: 384.000 km.

### Reglas y condiciones de la simulación

El usuario debe ingresar los parámetros iniciales de la nave respetando los rangos establecidos por el programa.

Una vez cargados los datos, puede iniciar la simulación y observar el desplazamiento de Orion mediante una representación ASCII.

Durante el recorrido, el programa calcula la aceleración, actualiza la velocidad y la posición, y almacena los resultados obtenidos.

La simulación finaliza cuando la nave alcanza el límite lunar establecido en el modelo, deja de avanzar o alcanza el tiempo máximo permitido.

Se utiliza un modelo físico simplificado en una dimensión, con la Tierra y la Luna consideradas fijas. No representa una trayectoria orbital real ni un retorno libre completo.

## 3. Funcionamiento del programa

### El programa presenta un menú principal con cinco opciones:


1. **Cargar datos iniciales: permite ingresar la velocidad, masa, altura orbital e intervalo de almacenamiento de muestras.**
2. **Mostrar constantes físicas: presenta las constantes utilizadas en los cálculos.**
3. **Ejecutar simulación: calcula el movimiento de Orion y muestra su posición mediante caracteres ASCII.**
4. **Mostrar resultados: presenta el historial de la simulación, los eventos importantes y el análisis energético.**
5. **Salir: finaliza la ejecución del programa.**

### **Organización del código**

**Para facilitar su comprensión, mantenimiento y desarrollo, el proyecto fue dividido en cinco archivos principales:**

* **main.c: contiene la función principal y administra el menú.**
* **simulador.h: contiene las constantes físicas, las estructuras de datos y las declaraciones de las funciones del simulador.**
* **simulador.c: desarrolla los cálculos físicos, la ejecución de la simulación, el almacenamiento de información y los reportes.**
* **validaciones.h: declara las funciones encargadas de validar los datos.**
* **validaciones.c: implementa las validaciones de entradas numéricas y rangos permitidos.**

### **Estructuras de datos utilizadas**

**Se implementó una lista simplemente enlazada para almacenar las muestras del recorrido. Cada nodo contiene información sobre el tiempo, la distancia, la velocidad y las energías de Orion.**

**También se utilizó un arreglo de registros para almacenar eventos importantes de la misión.**

**Además, se emplearon punteros, memoria dinámica mediante malloc y liberación de memoria mediante free.**


## 4. Compilación y ejecución

 \n 