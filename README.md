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

En la carpeta que contiene los `.c` y `.h`:

Windows con GCC (MinGW-w64):

```powershell
gcc -std=c11 -Wall -Wextra -Wpedantic main.c simulador.c validaciones.c -o artemis.exe -lm
.\artemis.exe
```

También se puede ejecutar `compilar.bat` para compilar.

Linux/macOS con GCC:

```bash
make
./artemis
```

 \n 

## 5. Metodología de desarrollo y trabajo colaborativo

### Desarrollo inicial en pseudocódigo

Como primera etapa, realizamos el planteamiento y desarrollo del algoritmo utilizando el *pseudocódigo trabajado en la cátedra de Algoritmos y Estructuras de Datos*.

Esto nos permitió organizar la solución antes de comenzar a programar, identificar las variables necesarias, establecer los procesos principales y definir las estructuras de datos que utilizaríamos.

También analizamos el funcionamiento del menú, los cálculos físicos, las validaciones y la forma de almacenar los resultados de la simulación.

Una vez definida la lógica del programa, comenzamos a trasladar progresivamente el pseudocódigo al lenguaje C, adaptando las instrucciones y las estructuras a la sintaxis propia del lenguaje.

### Organización y coordinación del equipo

El desarrollo se organizó mediante el trabajo colaborativo de los cuatro integrantes.

Para ello, nos pusimos de acuerdo sobre qué partes debía desarrollar, revisar o integrar cada uno, procurando distribuir las responsabilidades de manera equilibrada.

Decidimos modularizar el programa en diferentes archivos para evitar concentrar todas las instrucciones en un único archivo fuente.

Esta organización permitió trabajar sobre distintas funcionalidades, como el menú principal, las validaciones, los cálculos físicos, las estructuras de datos y la presentación de resultados.

### Uso de Git y GitHub

Utilizamos GitHub como repositorio compartido para organizar y registrar los avances del proyecto.

Mediante Git pudimos descargar las actualizaciones del repositorio, incorporar modificaciones y realizar commits descriptivos para identificar los cambios efectuados.

También coordinamos entre los integrantes qué modificaciones se incorporarían al repositorio, con el objetivo de reducir conflictos y mantener una estructura ordenada.

El trabajo colaborativo nos permitió comprender mejor la importancia de la modularización, la comunicación entre integrantes y la integración de diferentes partes de un mismo programa.

## 6. Registro del uso de Inteligencia Artificial

Durante el desarrollo del trabajo utilizamos ChatGPT, de OpenAI, como herramienta de apoyo para comprender conceptos, analizar alternativas de implementación y asistir en la construcción del programa en C.

Su utilización incluyó las siguientes actividades:

* Organización del algoritmo: asistencia para analizar el pseudocódigo inicial y su adaptación al lenguaje C.
* Modularización: propuestas para organizar el proyecto en archivos .c y .h, separando las declaraciones de las implementaciones.
* Generación y revisión de código: propuestas de implementación de funciones, estructuras de datos, cálculos físicos y validaciones.
* Comprensión de conceptos: explicaciones sobre punteros, uso de static, void, registros, listas enlazadas y memoria dinámica.
* Cálculos físicos: asistencia para representar las fuerzas gravitatorias y las energías utilizadas por el simulador.
* Compilación y GitHub: orientación sobre comandos de compilación, gestión de ramas, actualización del repositorio y registro de cambios.
* Documentación: asistencia para organizar y redactar el presente archivo README.

La inteligencia artificial se utilizó como una herramienta de consulta y asistencia técnica. Las propuestas obtenidas se incorporaron al proceso de desarrollo y estudio del proyecto, procurando comprender las instrucciones y su relación con los contenidos de la materia.

El equipo es responsable de revisar, probar, integrar y explicar el funcionamiento del código presentado.


## 7. Conclusión

El desarrollo de este trabajo nos permitió aplicar de manera práctica los contenidos estudiados durante la materia.

Partimos de un algoritmo expresado en pseudocódigo y avanzamos hacia su implementación en C, incorporando funciones, estructuras de control, registros, arreglos, listas enlazadas, punteros y memoria dinámica.

Además de los aspectos técnicos, el proyecto nos permitió trabajar de manera coordinada, distribuir responsabilidades y utilizar GitHub como herramienta de colaboración.

Como resultado, desarrollamos un simulador modular que relaciona los conceptos de programación con un escenario físico basado en la misión Artemis.


