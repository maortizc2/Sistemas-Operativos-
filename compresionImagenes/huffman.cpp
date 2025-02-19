#include "huffman.h"
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <queue>
#include <unordered_map>
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

void compress_file(const std::string& filename) {
    int fd = open(filename.c_str(), O_RDONLY);
    if (fd == -1) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }
    
    struct stat fileStat;
    fstat(fd, &fileStat);
    size_t fileSize = fileStat.st_size;
    
    std::vector<unsigned char> data(fileSize);
    read(fd, data.data(), fileSize);
    close(fd);
    
    std::unordered_map<unsigned char, int> freq_table;
    build_frequency_table(data, freq_table);
    HuffmanNode* root = build_huffman_tree(freq_table);
    std::unordered_map<unsigned char, std::string> huffman_codes;
    build_huffman_codes(root, "", huffman_codes);
    
    int out_fd = open((filename + ".huff").c_str(), O_WRONLY | O_CREAT, 0644);
    if (out_fd == -1) {
        std::cerr << "Error opening output file" << std::endl;
        return;
    }
    
    for (const auto& pair : freq_table) {
        write(out_fd, &pair.first, 1);
        write(out_fd, &pair.second, sizeof(pair.second));
    }
    char delimiter = '\0';
    write(out_fd, &delimiter, 1);
    
    std::string bitstream;
    for (unsigned char byte : data) {
        bitstream += huffman_codes[byte];
    }
    
    unsigned char byte = 0;
    int bit_count = 0;
    for (char bit : bitstream) {
        byte = (byte << 1) | (bit - '0');
        bit_count++;
        if (bit_count == 8) {
            write(out_fd, &byte, 1);
            byte = 0;
            bit_count = 0;
        }
    }
    if (bit_count > 0) {
        byte <<= (8 - bit_count);
        write(out_fd, &byte, 1);
    }
    close(out_fd);
}

void decompress_file(const std::string& filename) {
    int fd = open(filename.c_str(), O_RDONLY);
    if (fd == -1) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }
    
    std::unordered_map<unsigned char, int> freq_table;
    unsigned char byte;
    while (read(fd, &byte, 1) > 0) {
        if (byte == '\0') break;
        int freq;
        read(fd, &freq, sizeof(freq));
        freq_table[byte] = freq;
    }
    
    HuffmanNode* root = build_huffman_tree(freq_table);
    
    int out_fd = open((filename + ".decompressed").c_str(), O_WRONLY | O_CREAT, 0644);
    if (out_fd == -1) {
        std::cerr << "Error opening output file" << std::endl;
        close(fd);
        return;
    }
    
    HuffmanNode* current = root;
    unsigned char bitBuffer;
    while (read(fd, &bitBuffer, 1) > 0) {
        for (int i = 7; i >= 0; --i) {
            current = (bitBuffer & (1 << i)) ? current->right : current->left;
            if (!current->left && !current->right) {
                write(out_fd, &current->data, 1);
                current = root;
            }
        }
    }
    close(fd);
    close(out_fd);
}
