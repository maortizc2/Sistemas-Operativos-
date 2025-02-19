#include "huffman.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <bitset>
#include <vector>
#include <string>


void build_frequency_table(const std::vector<unsigned char>& data, std::unordered_map<unsigned char, int>& freq_table) {
    for (unsigned char byte : data) {
        freq_table[byte]++;
    }
}

HuffmanNode* build_huffman_tree(const std::unordered_map<unsigned char, int>& freq_table) {
    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, Compare> minHeap;
    for (const auto& pair : freq_table) {
        minHeap.push(new HuffmanNode(pair.first, pair.second));
    }
    
    while (minHeap.size() > 1) {
        HuffmanNode* left = minHeap.top(); minHeap.pop();
        HuffmanNode* right = minHeap.top(); minHeap.pop();
        HuffmanNode* parent = new HuffmanNode('\0', left->freq + right->freq);
        parent->left = left;
        parent->right = right;
        minHeap.push(parent);
    }
    
    return minHeap.top();
}

void build_huffman_codes(HuffmanNode* root, std::string code, std::unordered_map<unsigned char, std::string>& huffman_codes) {
    if (!root) return;
    if (root->left == nullptr && root->right == nullptr) {
        huffman_codes[root->data] = code;
    }
    build_huffman_codes(root->left, code + "0", huffman_codes);
    build_huffman_codes(root->right, code + "1", huffman_codes);
}

void write_bitstream(std::ofstream& output, const std::string& bitstream) {
    // Escribir la secuencia de bits en bytes
    unsigned char byte = 0;
    int bit_count = 0;
    for (char bit : bitstream) {
        byte = (byte << 1) | (bit - '0');  // Desplazar y agregar el bit
        bit_count++;
        if (bit_count == 8) {
            output.put(byte);  // Escribir el byte
            byte = 0;
            bit_count = 0;
        }
    }
    
    // Si hay bits sobrantes (menos de 8 bits), agregar un byte con el valor correspondiente
    if (bit_count > 0) {
        byte <<= (8 - bit_count);  // Rellenar con ceros
        output.put(byte);
    }
}

void compress_file(const std::string& filename) {
    std::ifstream input(filename, std::ios::binary);
    if (!input) {
        std::cerr << "Error opening file for reading: " << filename << std::endl;
        return;
    }
    
    std::vector<unsigned char> data((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
    input.close();
    
    std::unordered_map<unsigned char, int> freq_table;
    build_frequency_table(data, freq_table);
    
    HuffmanNode* root = build_huffman_tree(freq_table);
    std::unordered_map<unsigned char, std::string> huffman_codes;
    build_huffman_codes(root, "", huffman_codes);
    
    std::ofstream output(filename + ".huff", std::ios::binary);
    if (!output) {
        std::cerr << "Error opening file for writing: " << filename + ".huff" << std::endl;
        return;
    }
    
    // Guardar la tabla de frecuencias para descompresión (esto debería ser más eficiente en una implementación real)
    for (const auto& pair : freq_table) {
        output.put(pair.first);        // Escribir el byte
        output.write(reinterpret_cast<const char*>(&pair.second), sizeof(pair.second));   // Escribir la frecuencia
    }

    // Escribir un delimitador para indicar el final de la tabla de frecuencias
    output.put('\0');  // Usamos un byte nulo como delimitador
    
    // Escribir la secuencia comprimida
    std::string bitstream;
    for (unsigned char byte : data) {
        bitstream += huffman_codes[byte];
    }
    
    write_bitstream(output, bitstream);
    output.close();
}

void decompress_file(const std::string& filename) {
    std::ifstream input(filename, std::ios::binary);
    if (!input) {
        std::cerr << "Error opening file for reading: " << filename << std::endl;
        return;
    }
    
    // Recuperar la tabla de frecuencias
    std::unordered_map<unsigned char, int> freq_table;
    char ch;
    while (input.get(ch)) {
        unsigned char byte = static_cast<unsigned char>(ch);
        if (byte == '\0') {
            break;  // Fin de la tabla de frecuencias
        }
        int freq;
        input.read(reinterpret_cast<char*>(&freq), sizeof(freq));
        if (!input) {
            std::cerr << "Error reading frequency table." << std::endl;
            return;
        }
        freq_table[byte] = freq;
    }

    // Reconstruir el árbol de Huffman a partir de la tabla de frecuencias
    HuffmanNode* root = build_huffman_tree(freq_table);

    // Abrir el archivo de salida
    std::ofstream output(filename + ".decompressed", std::ios::binary);
    if (!output) {
        std::cerr << "Error opening file for writing: " << filename + ".decompressed" << std::endl;
        delete root;
        return;
    }

    // Decodificar la secuencia de bits
    HuffmanNode* current = root;
    char bit;
    while (input.get(bit)) {
        for (int i = 7; i >= 0; --i) {
            if (current->left == nullptr && current->right == nullptr) {
                output.put(current->data);
                current = root;
            }

            if ((bit >> i) & 1) {
                current = current->right;
            } else {
                current = current->left;
            }
        }
    }

    // Asegurarse de escribir el último carácter decodificado
    if (current->left == nullptr && current->right == nullptr) {
        output.put(current->data);
    }

    // Liberar memoria y cerrar archivos
    delete root;
    input.close();
    output.close();
}