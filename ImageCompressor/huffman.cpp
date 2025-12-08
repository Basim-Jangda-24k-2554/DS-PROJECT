#include "Huffman.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>

Huffman::Huffman() {
    root = nullptr;
}

Huffman::~Huffman() {
    freeTree(root);
}

// FREQUENCY TABLE
void Huffman::buildFrequencyTable(const unsigned char *pixels, int size, int freq[256]) {
    for (int i = 0; i < 256; i++) freq[i] = 0;
    for (int i = 0; i < size; i++) freq[pixels[i]]++;
}

//  HEAP FUNCTIONS
MinHeap* Huffman::createMinHeap(int capacity) {
    MinHeap *heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->size = 0;
    heap->capacity = capacity;
    heap->nodes = (HuffmanNode**)malloc(capacity * sizeof(HuffmanNode*));
    return heap;
}

void Huffman::insertMinHeap(MinHeap *heap, HuffmanNode *node) {
    heap->nodes[heap->size] = node;
    int i = heap->size;
    heap->size++;

    // Up-heap
    while (i && heap->nodes[i]->freq < heap->nodes[(i - 1) / 2]->freq) {
        HuffmanNode *temp = heap->nodes[i];
        heap->nodes[i] = heap->nodes[(i - 1) / 2];
        heap->nodes[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

HuffmanNode* Huffman::extractMin(MinHeap *heap) {
    if (heap->size == 0) return nullptr;
    HuffmanNode *temp = heap->nodes[0];
    heap->nodes[0] = heap->nodes[heap->size - 1];
    heap->size--;
    minHeapify(heap, 0);
    return temp;
}

void Huffman::minHeapify(MinHeap *heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size && heap->nodes[left]->freq < heap->nodes[smallest]->freq) smallest = left;
    if (right < heap->size && heap->nodes[right]->freq < heap->nodes[smallest]->freq) smallest = right;

    if (smallest != idx) {
        HuffmanNode *temp = heap->nodes[idx];
        heap->nodes[idx] = heap->nodes[smallest];
        heap->nodes[smallest] = temp;
        minHeapify(heap, smallest);
    }
}

void Huffman::freeMinHeap(MinHeap *heap) {
    free(heap->nodes);
    free(heap);
}

// BUILD HUFFMAN TREE
HuffmanNode* Huffman::buildHuffmanTree(int freq[256]) {
    MinHeap *heap = createMinHeap(256);

    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            HuffmanNode *node = (HuffmanNode*)malloc(sizeof(HuffmanNode));
            node->value = (unsigned char)i;
            node->freq = freq[i];
            node->left = node->right = nullptr;
            insertMinHeap(heap, node);
        }
    }

    while (heap->size > 1) {
        HuffmanNode *left = extractMin(heap);
        HuffmanNode *right = extractMin(heap);

        HuffmanNode *parent = (HuffmanNode*)malloc(sizeof(HuffmanNode));
        parent->value = 0;
        parent->freq = left->freq + right->freq;
        parent->left = left;
        parent->right = right;

        insertMinHeap(heap, parent);
    }

    HuffmanNode *rootNode = extractMin(heap);
    freeMinHeap(heap);
    return rootNode;
}

// GENERATE CODES
void Huffman::generateCodes(HuffmanNode *node, char codes[256][256], char code[], int top) {
    if (node->left) {
        code[top] = '0';
        generateCodes(node->left, codes, code, top + 1);
    }
    if (node->right) {
        code[top] = '1';
        generateCodes(node->right, codes, code, top + 1);
    }
    if (!node->left && !node->right) {
        code[top] = '\0';
        strcpy(codes[node->value], code);
    }
}

// BIT HANDLING
void Huffman::writeBit(FILE *fp, unsigned char bit, unsigned char &buffer, int &bitCount) {
    buffer <<= 1;
    buffer |= bit;
    bitCount++;
    if (bitCount == 8) {
        fputc(buffer, fp);
        buffer = 0;
        bitCount = 0;
    }
}

void Huffman::flushBuffer(FILE *fp, unsigned char &buffer, int &bitCount) {
    if (bitCount > 0) {
        buffer <<= (8 - bitCount);
        fputc(buffer, fp);
        buffer = 0;
        bitCount = 0;
    }
}

unsigned char Huffman::readBit(FILE *fp, unsigned char &buffer, int &bitCount) {
    if (bitCount == 0) {
        int c = fgetc(fp);
        if (c == EOF) return 0;
        buffer = (unsigned char)c;
        bitCount = 8;
    }
    unsigned char bit = (buffer & 0x80) >> 7;
    buffer <<= 1;
    bitCount--;
    return bit;
}

// ENCODE PIXELS
void Huffman::encodePixels(const unsigned char *pixels, int size, char codes[256][256], char *&bitstream, int &bitstreamSize) {

    int maxBits = size * 8 * 2;
    bitstream = (char*)malloc(maxBits);
    bitstreamSize = 0;

    for (int i = 0; i < size; i++) {
        char *code = codes[pixels[i]];
        for (int j = 0; code[j] != '\0'; j++) {
            bitstream[bitstreamSize++] = code[j];
        }
    }
}

// DECODE PIXELS
void Huffman::decodePixels(HuffmanNode *root, const char *bitstream, int bitstreamSize, unsigned char *pixels, int pixelCount) {
    int pixelIndex = 0;
    HuffmanNode *current = root;

    for (int i = 0; i < bitstreamSize && pixelIndex < pixelCount; i++) {
        if (bitstream[i] == '0') current = current->left;
        else current = current->right;

        if (!current->left && !current->right) {
            pixels[pixelIndex++] = current->value;
            current = root;
        }
    }
}

// FREE TREE
void Huffman::freeTree(HuffmanNode *node) {
    if (!node) return;
    freeTree(node->left);
    freeTree(node->right);
    free(node);
}

// COMPRESS TO FILE
bool Huffman::compressToFile(const unsigned char *pixels, int width, int height, const QString &outputFile) {
    int size = width * height;
    int freq[256];
    buildFrequencyTable(pixels, size, freq);

    root = buildHuffmanTree(freq);

    char codes[256][256];
    char code[256];
    for (int i = 0; i < 256; i++) codes[i][0] = '\0';
    generateCodes(root, codes, code, 0);

    char *bitstream;
    int bitstreamSize;
    encodePixels(pixels, size, codes, bitstream, bitstreamSize);

    // Save file
    FILE *fp = fopen(outputFile.toStdString().c_str(), "wb");
    if (!fp) return false;

    // Write width and height
    fwrite(&width, sizeof(int), 1, fp);
    fwrite(&height, sizeof(int), 1, fp);

    // Write frequency table
    fwrite(freq, sizeof(int), 256, fp);

    // Write bitstream as bytes
    unsigned char buffer = 0;
    int bitCount = 0;
    for (int i = 0; i < bitstreamSize; i++) {
        writeBit(fp, bitstream[i] - '0', buffer, bitCount);
    }
    flushBuffer(fp, buffer, bitCount);

    fclose(fp);
    free(bitstream);
    freeTree(root);
    root = nullptr;
    return true;
}

// DECOMPRESS FROM FILE
bool Huffman::decompressFromFile(unsigned char *&pixels, int &width, int &height, const QString &inputFile) {
    FILE *fp = fopen(inputFile.toStdString().c_str(), "rb");
    if (!fp) return false;

    fread(&width, sizeof(int), 1, fp);
    fread(&height, sizeof(int), 1, fp);
    int size = width * height;

    int freq[256];
    fread(freq, sizeof(int), 256, fp);

    root = buildHuffmanTree(freq);

    pixels = (unsigned char*)malloc(size);
    char *bitstream = (char*)malloc(size * 16); // temporary large buffer
    int bitstreamSize = 0;

    unsigned char buffer = 0;
    int bitCount = 0;
    int c;
    while ((c = fgetc(fp)) != EOF) {
        buffer = (unsigned char)c;
        for (int i = 0; i < 8; i++) {
            bitstream[bitstreamSize++] = ((buffer & 0x80) ? '1' : '0');
            buffer <<= 1;
        }
    }

    decodePixels(root, bitstream, bitstreamSize, pixels, size);

    fclose(fp);
    free(bitstream);
    freeTree(root);
    root = nullptr;
    return true;
}
