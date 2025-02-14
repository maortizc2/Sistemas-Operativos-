#ifndef RLE_H
#define RLE_H

#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

void mostrarAyuda();
void comprimir(const char* archivo);
void descomprimir(const char* archivo);

#endif // RLE_H