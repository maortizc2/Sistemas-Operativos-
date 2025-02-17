#include "FileEncryption.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        FileEncryption::showHelp();
        return 1;
    }

    std::string arg = argv[1];
    FileEncryption encryptor;

    if (arg == "-h" || arg == "--help") {
        FileEncryption::showHelp();
    }
    else if (arg == "-v" || arg == "--version") {
        FileEncryption::showVersion();
    }
    else if ((arg == "-e" || arg == "--encrypt") && argc == 3) {
        encryptor.encryptFile(argv[2]);
    }
    else if ((arg == "-d" || arg == "--decrypt") && argc == 3) {
        encryptor.decryptFile(argv[2]);
    }
    else {
        std::cerr << "Opción inválida o argumentos faltantes\n";
        FileEncryption::showHelp();
        return 1;
    }

    return 0;
}