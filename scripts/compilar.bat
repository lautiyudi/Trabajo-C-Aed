@echo off

REM Script para compilar el proyecto Artemis en Windows.
REM Requiere tener instalado GCC (por ejemplo, MinGW-w64).

REM Nos ubicamos en la carpeta principal del proyecto.
cd /d "%~dp0.."

REM Compilamos los archivos C y generamos artemis.exe.
REM Se utiliza el estandar C11 y se activan advertencias.
gcc -std=c11 -Wall -Wextra -Wpedantic main.c simulador.c validaciones.c -o artemis.exe -lm

REM Verificamos si ocurrio algun error al compilar.
if errorlevel 1 (
    echo Error de compilacion. Revise que GCC este instalado y el codigo sea correcto.
    pause
    exit /b 1
)

REM Si no hubo errores, informamos que la compilacion fue exitosa.
echo Compilacion correcta. Ejecute artemis.exe

REM Mantenemos la ventana abierta para ver el resultado.
pause
