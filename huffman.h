#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <QString>

// Node of Huffman tree
struct HuffmanNode {
    unsigned char value; // pixel value
    int freq;
    HuffmanNode *left;
    HuffmanNode *right;
};

// Min-heap for building Huffman tree
struct MinHeap {
    HuffmanNode **nodes;
    int size;
    int capacity;
};

class Huffman {
public:
    Huffman();
    ~Huffman();

    // Compress pixels and save to .huff file
    bool compressToFile(const unsigned char *pixels, int width, int height, const QString &outputFile);

    // Load .huff file and decompress to pixels
    bool decompressFromFile(unsigned char *&pixels, int &width, int &height, const QString &inputFile);

private:
    // Build frequency table
    void buildFrequencyTable(const unsigned char *pixels, int size, int freq[256]);

    // Heap functions
    MinHeap* createMinHeap(int capacity);
    void insertMinHeap(MinHeap *heap, HuffmanNode *node);
    HuffmanNode* extractMin(MinHeap *heap);
    void minHeapify(MinHeap *heap, int idx);
    void freeMinHeap(MinHeap *heap);

    // Build Huffman tree
    HuffmanNode* buildHuffmanTree(int freq[256]);

    // Generate codes recursively
    void generateCodes(HuffmanNode *node, char codes[256][256], char code[], int top);

    // Encode pixels
    void encodePixels(const unsigned char *pixels, int size, char codes[256][256], char *&bitstream, int &bitstreamSize);

    // Decode pixels
    void decodePixels(HuffmanNode *root, const char *bitstream, int bitstreamSize, unsigned char *pixels, int pixelCount);

    // Free tree
    void freeTree(HuffmanNode *node);

    // Helper functions for file read/write bits
    void writeBit(FILE *fp, unsigned char bit, unsigned char &buffer, int &bitCount);
    void flushBuffer(FILE *fp, unsigned char &buffer, int &bitCount);
    unsigned char readBit(FILE *fp, unsigned char &buffer, int &bitCount);

    // Root of Huffman tree (used temporarily during decompression)
    HuffmanNode *root;
};

#endif // HUFFMAN_H
