#include "FileEncryption.h"
#include <iostream>
#include <fcntl.h>
#include <unistd.h>

bool FileEncryption::isTextFile(const std::string& filename) {
    int fd = open(filename.c_str(), O_RDONLY);
    if (fd == -1) {
        std::cerr << "Error al abrir el archivo" << std::endl;
        return false;
    }
    
    unsigned char buffer[1024];
    ssize_t bytesRead = read(fd, buffer, sizeof(buffer));
    close(fd);
    
    for (ssize_t i = 0; i < bytesRead; i++) {
        if (buffer[i] == 0 || (buffer[i] < 32 && buffer[i] != '\n' && buffer[i] != '\t' && buffer[i] != '\r')) {
            return false;
        }
    }
    return true;
}

void FileEncryption::processFile(const std::string& inputFile, const std::string& outputFile, bool /* encrypt */) {
    int fdIn = open(inputFile.c_str(), O_RDONLY);
    if (fdIn == -1) {
        std::cerr << "Error al abrir el archivo de entrada" << std::endl;
        return;
    }

    int fdOut = open(outputFile.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fdOut == -1) {
        std::cerr << "Error al crear el archivo de salida" << std::endl;
        close(fdIn);
        return;
    }

    unsigned char buffer[1024];
    ssize_t bytesRead;

    while ((bytesRead = read(fdIn, buffer, sizeof(buffer))) > 0) {
        // Encriptar/desencriptar usando XOR
        for (ssize_t i = 0; i < bytesRead; i++) {
            buffer[i] ^= key;
        }
        
        if (write(fdOut, buffer, bytesRead) != bytesRead) {
            std::cerr << "Error al escribir en el archivo" << std::endl;
            break;
        }
    }

    close(fdIn);
    close(fdOut);
}

void FileEncryption::encryptFile(const std::string& inputFile) {
    std::cout << "Tipo de archivo: " << (isTextFile(inputFile) ? "texto" : "binario") << std::endl;
    std::string outputFile = inputFile + ".encrypted";
    processFile(inputFile, outputFile, true);
    std::cout << "Archivo encriptado guardado como: " << outputFile << std::endl;
}

void FileEncryption::decryptFile(const std::string& inputFile) {
    std::string outputFile = inputFile + ".decrypted";
    processFile(inputFile, outputFile, false);
    std::cout << "Archivo desencriptado guardado como: " << outputFile << std::endl;
}

void FileEncryption::showHelp() {
    std::cout << "Uso: ./fileencrypt [opción] <archivo>\n"
              << "Opciones:\n"
              << "  -h, --help\t\tMuestra este mensaje de ayuda\n"
              << "  -v, --version\t\tMuestra la versión del programa\n"
              << "  -e, --encrypt\t\tEncripta el archivo especificado\n"
              << "  -d, --decrypt\t\tDesencripta el archivo especificado\n";
}

void FileEncryption::showVersion() {
    std::cout << "FileEncrypt versión 1.0\n";
}