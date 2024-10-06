#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wav_parser.h"

/* Prints errors to stderr */
static void handle_error(const char *message) {
    fprintf(stderr, "%s\n", message);
}

/* Function to parse WAV file */
int parse_wav_file(const char *fileName, WAVFile *wavFile) {
    FILE *wavFilePtr = fopen(fileName, "rb");
    if (wavFilePtr == NULL) {
        handle_error("Failed to open WAV file.");
        return WAV_INVALID_FILE;
    }

    /* Read the RIFF header */
    if (fread(&wavFile->header, sizeof(WAVHeader), 1, wavFilePtr) != 1) {
        fclose(wavFilePtr);
        handle_error("Failed to read WAV header.");
        return WAV_INVALID_FILE;
    }

    if (strncmp(wavFile->header.riff, "RIFF", 4) != 0 || strncmp(wavFile->header.wave, "WAVE", 4) != 0) {
        fclose(wavFilePtr);
        handle_error("Invalid WAV file format.");
        return WAV_UNSUPPORTED_FORMAT;
    }

    /* Read the fmt chunk */
    if (fread(&wavFile->fmtChunk, sizeof(WAVFmtChunk), 1, wavFilePtr) != 1) {
        fclose(wavFilePtr);
        handle_error("Failed to read fmt chunk.");
        return WAV_INVALID_FILE;
    }

    if (strncmp(wavFile->fmtChunk.fmt, "fmt ", 4) != 0 || wavFile->fmtChunk.audioFormat != 1) {
        fclose(wavFilePtr);
        handle_error("Unsupported WAV format.");
        return WAV_UNSUPPORTED_FORMAT;
    }

    /* Read the data chunk */
    if (fread(&wavFile->dataChunk, sizeof(WAVDataChunk), 1, wavFilePtr) != 1) {
        fclose(wavFilePtr);
        handle_error("Failed to read data chunk.");
        return WAV_INVALID_FILE;
    }

    if (strncmp(wavFile->dataChunk.data, "data", 4) != 0) {
        fclose(wavFilePtr);
        handle_error("Invalid data chunk.");
        return WAV_UNSUPPORTED_FORMAT;
    }

    /* Allocate memory for audio data */
    wavFile->audioData = (int16_t*) malloc(wavFile->dataChunk.dataSize);
    if (wavFile->audioData == NULL) {
        fclose(wavFilePtr);
        handle_error("Memory allocation failed.");
        return WAV_ALLOCATION_FAILED;
    }

    /* Read the audio data */
    if (fread(wavFile->audioData, wavFile->dataChunk.dataSize, 1, wavFilePtr) != 1) {
        free(wavFile->audioData);
        fclose(wavFilePtr);
        handle_error("Failed to read audio data.");
        return WAV_INVALID_FILE;
    }

    fclose(wavFilePtr);
    return WAV_SUCCESS;
}

/* Function to print WAV information */
void print_wav_info(const WAVFile *wavFile) {
    printf("Audio Format: %u (PCM)\n", wavFile->fmtChunk.audioFormat);
    printf("Channels: %u\n", wavFile->fmtChunk.numChannels);
    printf("Sample Rate: %u Hz\n", wavFile->fmtChunk.sampleRate);
    printf("Bits per Sample: %u\n", wavFile->fmtChunk.bitsPerSample);
    printf("Data Size: %u bytes\n", wavFile->dataChunk.dataSize);
}

/* Free memory allocated for WAV data */
void free_wav_file(WAVFile *wavFile) {
    if (wavFile->audioData != NULL) {
        free(wavFile->audioData);
        wavFile->audioData = NULL;
    }
}
