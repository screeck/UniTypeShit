#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WINDOW_SIZE 4096
#define LOOKAHEAD_BUFFER_SIZE 18

typedef struct {
    unsigned short offset;
    unsigned char length;
    unsigned char symbol;
} LZ77Triplet;

// Function to compute CRC-32
unsigned int crc32(const unsigned char* data, size_t length) {
    unsigned int crc = 0xFFFFFFFF;
    for (size_t i = 0; i < length; i++) {
        crc ^= data[i];
        for (int j = 0; j < 8; j++) {
            if (crc & 1)
                crc = (crc >> 1) ^ 0xEDB88320;
            else
                crc >>= 1;
        }
    }
    return ~crc;
}

int findLongestMatch(const char* window, const char* lookahead, int* offset, int* length) {
    size_t windowLength = strlen(window);
    size_t lookaheadLength = strlen(lookahead);

    *offset = 0;
    *length = 0;

    for (int i = 1; i <= windowLength && i < WINDOW_SIZE; i++) {
        int matchLength = 0;
        while (matchLength < lookaheadLength &&
            window[windowLength - i + matchLength] == lookahead[matchLength]) {
            matchLength++;
        }

        if (matchLength > *length) {
            *length = matchLength;
            *offset = i;
        }

        // Early exit if the match spans the entire lookahead buffer
        if (matchLength == lookaheadLength) break;
    }

    return *length > 0;
}

void lz77Encode(const unsigned char* data, size_t dataSize, FILE* outputFile) {
    char window[WINDOW_SIZE + 1] = "";  // Ensure null-termination
    size_t position = 0;

    unsigned char* encodedData = malloc(dataSize * sizeof(LZ77Triplet)); // Store encoded triplets
    size_t encodedDataSize = 0;

    while (position < dataSize) {
        int offset = 0, length = 0;
        char lookahead[LOOKAHEAD_BUFFER_SIZE + 1] = "";
        strncpy(lookahead, (char*)data + position, LOOKAHEAD_BUFFER_SIZE);
        lookahead[LOOKAHEAD_BUFFER_SIZE] = '\0';  // Ensure null-termination

        findLongestMatch(window, lookahead, &offset, &length);

        unsigned char nextSymbol = (position + length < dataSize) ? data[position + length] : '\0';
        LZ77Triplet triplet = { offset, length, nextSymbol };
        fwrite(&triplet, sizeof(LZ77Triplet), 1, outputFile);

        // Store triplet for CRC calculation
        memcpy(encodedData + encodedDataSize, &triplet, sizeof(LZ77Triplet));
        encodedDataSize += sizeof(LZ77Triplet);

        int copyLength = length + 1;
        if (position + copyLength > dataSize) {
            copyLength = dataSize - position;
        }

        strncat(window, (char*)data + position, copyLength);
        if (strlen(window) > WINDOW_SIZE) {
            memmove(window, window + strlen(window) - WINDOW_SIZE, WINDOW_SIZE);
            window[WINDOW_SIZE] = '\0';  // Ensure null-termination
        }

        position += copyLength;
    }

    // Compute and write CRC
    unsigned int checksum = crc32(encodedData, encodedDataSize);
    fwrite(&checksum, sizeof(unsigned int), 1, outputFile);

    free(encodedData);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        return 1;
    }

    const char* inputFilePath = argv[1];
    const char* outputFilePath = argv[2];

    FILE* inputFile = fopen(inputFilePath, "rb");
    if (!inputFile) {
        fprintf(stderr, "Error opening input file: %s\n", inputFilePath);
        return 1;
    }

    fseek(inputFile, 0, SEEK_END);
    size_t fileSize = ftell(inputFile);
    rewind(inputFile);

    unsigned char* fileData = malloc(fileSize);
    if (!fileData) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(inputFile);
        return 1;
    }

    fread(fileData, 1, fileSize, inputFile);
    fclose(inputFile);

    FILE* outputFile = fopen(outputFilePath, "wb");
    if (!outputFile) {
        fprintf(stderr, "Error opening output file: %s\n", outputFilePath);
        free(fileData);
        return 1;
    }

    lz77Encode(fileData, fileSize, outputFile);
    fclose(outputFile);
    free(fileData);

    printf("Encoding complete. Data written to %s\n", outputFilePath);
    return 0;
}
