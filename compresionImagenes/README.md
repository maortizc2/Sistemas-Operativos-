# Compresor de imagenes - Algoritmo Huffman

## Que hace el programa?
Este programa implementa un compresor y descompresor de archivos utilizando el algoritmo de Huffman. Permite reducir el tamaño de archivos de testo y binarios de manera eficiente, basándose en la frecuencia de los caracteres dentro del archivo.

## Que archivos contiene? 

- huffman.cpp: tiene las funciones claves para implementar el algoritmo de Huffman.
- huffman.h: Contiene la definición de la estructura del nodo de Huffman y declara las funciones utilizadas en la compresión y descompresión de archivos.
- main.cpp:Es el punto de entrada del programa.
- Makefile: Facilita la compilación del programa.

## Como funciona la compresión?

- Se construye una tabla de frecuencias contando cuántas veces aparece cada byte en el archivo.
- Se genera un árbol de Huffman con base en la tabla de frecuencias.
- Se asignan códigos binarios más cortos a los bytes más frecuentes.
- Se almacena la tabla de frecuencias en el archivo comprimido (para la descompresión).
- Se codifica el archivo original con los códigos de Huffman.

## Que se podria mejorar?

- la implementación maneja la tabla de frecuencias de forma simple, lo que podría optimizarse para mejorar la velocidad y el tamaño del archivo comprimido.

