# Compilador utilizado
CC = gcc

# Estandar C11, advertencias y optimizacion
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -O2

# Biblioteca matematica
LDLIBS = -lm

# Compilacion del programa Artemis
artemis: main.o simulador.o validaciones.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

# Dependencias de cada modulo
main.o: main.c simulador.h validaciones.h
simulador.o: simulador.c simulador.h validaciones.h
validaciones.o: validaciones.c validaciones.h

# Eliminar archivos generados durante la compilacion
clean:
	rm -f artemis artemis.exe main.o simulador.o validaciones.o

.PHONY: clean
