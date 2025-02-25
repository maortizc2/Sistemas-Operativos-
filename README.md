# Compresor RLE - Proyecto de Sistemas Operativos

¡Hola profe! Este es mi proyecto para la asignatura de Sistemas Operativos. Implementé un programa para comprimir y descomprimir archivos utilizando el algoritmo RLE (Run-Length Encoding) mediante llamadas al sistema que vimos en clase.

## ¿Qué hace el programa?

- Comprime archivos usando el algoritmo RLE (Run-Length Encoding)
- Descomprime archivos previamente comprimidos con RLE
- Utiliza exclusivamente llamadas al sistema de bajo nivel (open, read, write, close)
- Interfaz por línea de comandos simple y directa
- No requiere dependencias externas

## ¿Cómo funciona la compresión RLE?

El algoritmo es bastante intuitivo:
- Recorre el archivo byte por byte
- Cuenta cuántas veces aparece consecutivamente cada byte
- Escribe el contador seguido del byte en el archivo comprimido
- Funciona especialmente bien con archivos que contienen secuencias largas de bytes repetidos

Ejemplo:
```
Texto original:  AAAAAABBBCDDDD
Comprimido RLE: 6A3B1C4D (donde cada número representa la cantidad de repeticiones)
```

## Requisitos del sistema

- Sistema operativo Linux
- Compilador G++ (soporte C++11 o superior)
- Make (opcional, para facilitar la compilación)

## Compilación

Para compilar el programa, ejecuta en la terminal:

```bash
g++ -o rle main.cpp rle.cpp
```

O si prefieres usar Make (creando un Makefile):

```bash
make
```

## Uso del programa

El programa tiene varios comandos:

1. Mostrar ayuda:
```bash
./rle -h
# o
./rle --help
```

2. Comprimir un archivo:
```bash
./rle -c archivo.txt
# Genera: archivo.txt.rle
```

3. Descomprimir un archivo:
```bash
./rle -x archivo.txt.rle
# Genera: Descomprimidoarchivo.txt
```

## Ejemplos de uso

### Comprimir un archivo de texto

```bash
echo "AAAAAABBBCDDDD" > test.txt
./rle -c test.txt
```

Resultado:
```
Archivo comprimido: test.txt.rle
```

### Descomprimir el archivo

```bash
./rle -x test.txt.rle
```

Resultado:
```
Archivo descomprimido: Descomprimidotest.txt
```

Para verificar que funciona:
```bash
cat Descomprimidotest.txt
# Debería mostrar: AAAAAABBBCDDDD
```

## Estructura del proyecto

- `main.cpp`: Maneja los argumentos de línea de comandos
- `rle.h`: Declaraciones de funciones y constantes
- `rle.cpp`: Implementación de las funciones de compresión y descompresión

## Detalles de implementación

El programa utiliza las llamadas al sistema POSIX:
- `open()`: Para abrir los archivos de entrada y salida
- `read()`: Para leer los datos del archivo de entrada
- `write()`: Para escribir los datos comprimidos/descomprimidos
- `close()`: Para cerrar los descriptores de archivo

## Limitaciones actuales

- El contador está limitado a 255 repeticiones (usa un byte)
- No se realiza verificación de integridad de los archivos comprimidos
- Los nombres de los archivos descomprimidos podrían ser más intuitivos
- No muestra estadísticas de compresión (tasa de compresión)

## Posibles mejoras futuras

Si tuviera más tiempo, podría:
- Implementar un esquema de escape para manejar más de 255 repeticiones
- Añadir verificación de integridad (checksums)
- Mejorar el nombramiento de archivos descomprimidos
- Añadir estadísticas de compresión
- Implementar compresión de carpetas completas
- Añadir una interfaz gráfica simple
