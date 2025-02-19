#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <unordered_map>
#include <vector>
#include <string>

// Nodo del árbol de Huffman
struct HuffmanNode {
    unsigned char data;
    int freq;
    HuffmanNode *left, *right;

    HuffmanNode(unsigned char d, int f)
        : data(d), freq(f), left(nullptr), right(nullptr) {}

    // Destructor para liberar la memoria de los nodos hijos
    ~HuffmanNode() {
        delete left;
        delete right;
    }
};

// Comparador para usar en el priority_queue
struct Compare {
    bool operator()(const HuffmanNode* l, const HuffmanNode* r) const {
        return l->freq > r->freq;
    }
};

void compress_file(const std::string &filename);
void decompress_file(const std::string &filename);

#endif // HUFFMAN_H

