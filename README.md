# TRABAJO FINAL INTEGRADOR — LABORATORIO DE C

## 1. Integrantes y comisión

*Carrera:* Ingeniería en Sistemas de Información  
*Universidad:* Universidad Tecnológica Nacional — Facultad Regional Resistencia  
*Materia:* Algoritmos y Estructuras de Datos  
*Comisión:* 1.1 (A)

*Integrantes:*
- Iván Gabriel Bulacio Báez
- Lucas Alfonso Gurrieri Agustini
- Lucas Emanuel Monticelli
- Lautaro Amir Yudi

## 2. Descripción del proyecto

### Simulador Artemis — Escenario 3: Inyección Translunar (TLI)

El proyecto consiste en desarrollar un simulador en lenguaje C basado en la misión Artemis, específicamente en la etapa de inyección translunar de la nave Orión.

El objetivo es representar el comportamiento de la nave durante su desplazamiento desde las proximidades de la Tierra hacia la Luna, considerando la influencia de las fuerzas gravitatorias de ambos cuerpos.

Para ello, el programa utiliza conceptos de la Primera Ley de Newton, la gravitación universal y las energías cinética, potencial y mecánica.

La simulación utiliza como valores de referencia:

- Velocidad inicial: 10.900 m/s.
- Masa de la nave Orion: 26.000 kg.
- Altura orbital inicial: 192 km.
- Distancia media entre la Tierra y la Luna: 384.000 km.

### Reglas y condiciones de la simulación

El usuario debe ingresar los parámetros iniciales de la nave respetando los rangos establecidos por el programa.

Una vez cargados los datos, puede iniciar la simulación y observar el desplazamiento de Orion mediante una representación ASCII.

Durante el recorrido, el programa calcula la aceleración, actualiza la velocidad y la posición, y almacena los resultados obtenidos.

La simulación finaliza cuando la nave alcanza el límite lunar establecido en el modelo, deja de avanzar o alcanza el tiempo máximo permitido.

Se utiliza un modelo físico simplificado en una dimensión, con la Tierra y la Luna consideradas fijas. No representa una trayectoria orbital real ni un retorno libre completo.