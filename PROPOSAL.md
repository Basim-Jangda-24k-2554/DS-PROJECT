# Image Compression using Huffman Coding (C++ & Qt)

|id|Name|
k24-2554 Basim Jangda
k24-2563 Ayyan Karar

## Introduction
This project aims to implement a lossless image compression application using the Huffman Coding algorithm in C++ with a Qt-based GUI. The application will take an image as input, compress it using Huffman encoding, and allow users to view both the original and compressed versions, along with details such as compression ratio and file size difference.

## Description
This project implements a lossless image compression system using Huffman Coding in C++ with a Qt-based GUI. The program reads an image, analyzes the frequency of its pixel values, and builds a Huffman Tree to generate binary codes that represent each pixel efficiently. The encoded data is then stored in a compressed file, which can later be decompressed to reconstruct the original image without quality loss.

The GUI allows users to select an image, perform compression and decompression, and view both the original and reconstructed images side by side. It also displays important statistics such as the compression ratio and file size reduction.

| **Data Structure**            | **Purpose**                                        |
| ----------------------------- | -------------------------------------------------- |
| **Array**                     | Store pixel values of the image                    |
| **Struct / Class**            | Represent nodes in the Huffman tree                |
| **Binary Tree**               | Build Huffman Tree for hierarchical encoding       |
| **Priority Queue (Min-Heap)** | Efficiently select nodes with smallest frequencies |
| **Hash Table / Map**          | Store Huffman codes for each pixel value           |
| **String / Bit Manipulation** | Build and store Huffman binary codes               |

Note: This is a rough idea and some things can change

