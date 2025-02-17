#ifndef FILE_ENCRYPTION_H
#define FILE_ENCRYPTION_H

#include <string>

class FileEncryption {
private:
    // Clave de encriptación simple
    const unsigned char key = 0xAE;
    
    // Método auxiliar para el procesamiento de archivos
    void processFile(const std::string& inputFile, const std::string& outputFile, bool encrypt);
    bool isTextFile(const std::string& filename);

public:
    // Constructor por defecto
    FileEncryption() = default;
    
    // Métodos principales
    void encryptFile(const std::string& inputFile);
    void decryptFile(const std::string& inputFile);
    
    // Métodos de utilidad
    static void showHelp();
    static void showVersion();
};

#endif