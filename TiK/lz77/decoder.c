#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WINDOW_SIZE 4096

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

void lz77Decode(const char* inputFileName, char* outputText) {
    FILE* inputFile = fopen(inputFileName, "rb");
    if (!inputFile) {
        fprintf(stderr, "Error opening file\n");
        exit(1);
    }

    // Determine file size
    fseek(inputFile, 0, SEEK_END);
    size_t fileSize = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET);

    size_t dataSize = fileSize - sizeof(unsigned int); // Exclude CRC size
    unsigned char* encodedData = malloc(dataSize);
    fread(encodedData, 1, dataSize, inputFile);

    // Read CRC from file
    unsigned int storedChecksum;
    fread(&storedChecksum, sizeof(unsigned int), 1, inputFile);

    // Compute CRC for validation
    unsigned int computedChecksum = crc32(encodedData, dataSize);
    if (computedChecksum != storedChecksum) {
        fprintf(stderr, "Data integrity check failed! Exiting.\n");
        free(encodedData);
        fclose(inputFile);
        exit(1);
    }

    char window[WINDOW_SIZE + 1] = "";  // Sliding window buffer
    size_t windowLength = 0;           // Current window length
    size_t outputLength = 0;           // Current output text length

    size_t offset = 0;
    while (offset < dataSize) {
        LZ77Triplet* triplet = (LZ77Triplet*)(encodedData + offset);
        offset += sizeof(LZ77Triplet);

        if (triplet->length > 0) {
            size_t matchStart = windowLength > triplet->offset ? windowLength - triplet->offset : 0;
            for (int i = 0; i < triplet->length; i++) {
                char matchChar = window[matchStart + i];
                outputText[outputLength++] = matchChar;

                // Append to the window
                if (windowLength < WINDOW_SIZE) {
                    window[windowLength++] = matchChar;
                }
                else {
                    memmove(window, window + 1, WINDOW_SIZE - 1);
                    window[WINDOW_SIZE - 1] = matchChar;
                }
            }
        }

        if (triplet->symbol != '\0') {
            outputText[outputLength++] = triplet->symbol;

            // Append to the window
            if (windowLength < WINDOW_SIZE) {
                window[windowLength++] = triplet->symbol;
            }
            else {
                memmove(window, window + 1, WINDOW_SIZE - 1);
                window[WINDOW_SIZE - 1] = triplet->symbol;
            }
        }
    }

    outputText[outputLength] = '\0';  // Null-terminate the output text
    free(encodedData);
    fclose(inputFile);
}

int main() {
    const char* inputFileName = "C:\\Users\\mjank\\Desktop\\output.bin";
    char outputText[1024] = "";  // Adjust size as needed

    lz77Decode(inputFileName, outputText);

    printf("Decoded text: %s\n", outputText);
    return 0;
}
