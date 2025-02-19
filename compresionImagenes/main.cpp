#include "huffman.h"
#include <iostream>
#include <cstring>

void show_help() {
    std::cout << "Uso: compressor [opciones] <archivo>\n"
              << "Opciones:\n"
              << "  -h, --help          Muestra este mensaje\n"
              << "  -v, --version       Muestra la versión del programa\n"
              << "  -c, --compress      Comprime el archivo indicado\n"
              << "  -x, --decompress    Descomprime el archivo indicado\n";
}

void show_version() {
    std::cout << "Compressor v1.0 - Implementación de Huffman\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        show_help();
        return 1;
    }
    
    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        show_help();
    } else if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0) {
        show_version();
    } else if ((strcmp(argv[1], "-c") == 0 || strcmp(argv[1], "--compress") == 0) && argc == 3) {
        compress_file(argv[2]);
    } else if ((strcmp(argv[1], "-x") == 0 || strcmp(argv[1], "--decompress") == 0) && argc == 3) {
        decompress_file(argv[2]);
    } else {
        std::cerr << "Opción no válida. Usa -h o --help para ver las opciones.\n";
        return 1;
    }
    
    return 0;
}
