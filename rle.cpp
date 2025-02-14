#include "rle.h"

using namespace std;

void mostrarAyuda() {
    cout << "Uso: rle [opciones] <archivo>\n"
         << "Opciones:\n"
         << "  -h, --help       Muestra esta ayuda.\n"
         << "  -c <archivo>     Comprime el archivo.\n"
         << "  -x <archivo>     Descomprime el archivo.\n";
}

void comprimir(const char* archivo) {
    int fd = open(archivo, O_RDONLY);
    if (fd < 0) {
        cerr << "Error: No se pudo abrir el archivo.\n";
        return;
    }

    string archivoSalida = string(archivo) + ".rle";
    int fd_out = open(archivoSalida.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_out < 0) {
        cerr << "Error: No se pudo crear el archivo comprimido.\n";
        close(fd);
        return;
    }

    char actual, previo;
    unsigned char contador = 0;
    ssize_t bytesLeidos;

    if (read(fd, &previo, 1) > 0) {
        contador = 1;
        while ((bytesLeidos = read(fd, &actual, 1)) > 0) {
            if (actual == previo && contador < 255) {
                contador++;
            } else {
                write(fd_out, &contador, 1);
                write(fd_out, &previo, 1);
                previo = actual;
                contador = 1;
            }
        }
        write(fd_out, &contador, 1);
        write(fd_out, &previo, 1);
    }

    close(fd);
    close(fd_out);
    cout << "Archivo comprimido: " << archivoSalida << endl;
}

void descomprimir(const char* archivo) {
    int fd = open(archivo, O_RDONLY);
    if (fd < 0) {
        cerr << "Error: No se pudo abrir el archivo comprimido.\n";
        return;
    }

    string archivoSalida = "Descomprimido" + string(archivo);
    size_t pos = archivoSalida.find(".rle");
    if (pos != string::npos) {
        archivoSalida.erase(pos);
    }

    int fd_out = open(archivoSalida.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_out < 0) {
        cerr << "Error: No se pudo crear el archivo descomprimido.\n";
        close(fd);
        return;
    }

    unsigned char contador;
    char caracter;
    ssize_t bytesLeidos;

    while ((bytesLeidos = read(fd, &contador, 1)) > 0) {
        if (read(fd, &caracter, 1) > 0) {
            for (int i = 0; i < contador; i++) {
                write(fd_out, &caracter, 1);
            }
        }
    }

    close(fd);
    close(fd_out);
    cout << "Archivo descomprimido: " << archivoSalida << endl;
}