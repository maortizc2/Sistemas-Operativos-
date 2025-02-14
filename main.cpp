#include <iostream>
#include <cstring>
#include "rle.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Error: Se requieren argumentos.\n";
        mostrarAyuda();
        return 1;
    }

    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        mostrarAyuda();
        return 0;
    }

    if (strcmp(argv[1], "-c") == 0 && argc == 3) {
        comprimir(argv[2]);
        return 0;
    }

    if (strcmp(argv[1], "-x") == 0 && argc == 3) {
        descomprimir(argv[2]);
        return 0;
    }

    std::cerr << "Error: Argumentos inválidos.\n";
    mostrarAyuda();
    return 1;
}