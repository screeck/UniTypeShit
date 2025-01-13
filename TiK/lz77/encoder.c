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

void lz77Encode(const char* text, FILE* outputFile) {
    int textLength = strlen(text);
    char window[WINDOW_SIZE + 1] = "";  // Ensure null-termination
    int position = 0;

    unsigned char* encodedData = malloc(textLength * sizeof(LZ77Triplet)); // Store encoded triplets
    size_t encodedDataSize = 0;

    while (position < textLength) {
        int offset = 0, length = 0;
        char lookahead[LOOKAHEAD_BUFFER_SIZE + 1] = "";
        strncpy(lookahead, text + position, LOOKAHEAD_BUFFER_SIZE);
        lookahead[LOOKAHEAD_BUFFER_SIZE] = '\0';  // Ensure null-termination

        findLongestMatch(window, lookahead, &offset, &length);

        char nextSymbol = (position + length < textLength) ? text[position + length] : '\0';
        LZ77Triplet triplet = { offset, length, nextSymbol };
        fwrite(&triplet, sizeof(LZ77Triplet), 1, outputFile);

        // Store triplet for CRC calculation
        memcpy(encodedData + encodedDataSize, &triplet, sizeof(LZ77Triplet));
        encodedDataSize += sizeof(LZ77Triplet);

        int copyLength = length + 1;
        if (position + copyLength > textLength) {
            copyLength = textLength - position;
        }

        strncat(window, text + position, copyLength);
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

int main() {
    const char* inputText = "siemasiema";
    FILE* outputFile = fopen("C:\\Users\\mjank\\Desktop\\output.bin", "wb");
    if (!outputFile) {
        fprintf(stderr, "Error opening file\n");
        return 1;
    }

    lz77Encode(inputText, outputFile);
    fclose(outputFile);

    printf("Encoding complete. Data written to file\n");
    return 0;
}
