#ifndef WAV_PARSER_H
#define WAV_PARSER_H

#include <stdint.h>

/* Error codes for better I/O feedback */
#define WAV_SUCCESS 0
#define WAV_INVALID_FILE -1
#define WAV_UNSUPPORTED_FORMAT -2
#define WAV_ALLOCATION_FAILED -3

/* WAV file structure for holding header and audio data */
typedef struct {
    char riff[4];        /* 'RIFF' */
    uint32_t chunkSize;  /* Size of file minus 8 bytes */
    char wave[4];        /* 'WAVE' */
} WAVHeader;

typedef struct {
    char fmt[4];         /* 'fmt ' */
    uint32_t subchunkSize;
    uint16_t audioFormat; /* Audio format (1 = PCM) */
    uint16_t numChannels; /* Number of channels (1=Mono, 2=Stereo) */
    uint32_t sampleRate;  /* Sample rate (Hz) */
    uint32_t byteRate;
    uint16_t blockAlign;
    uint16_t bitsPerSample;
} WAVFmtChunk;

typedef struct {
    char data[4];        /* 'data' */
    uint32_t dataSize;   /* Number of bytes in data section */
} WAVDataChunk;

typedef struct {
    WAVHeader header;    /* WAV header */
    WAVFmtChunk fmtChunk; /* Format subchunk */
    WAVDataChunk dataChunk; /* Data subchunk */
    int16_t *audioData;  /* Audio data */
} WAVFile;

/* Function Prototypes */
/* Parse a WAV file, return error codes on failure */
int parse_wav_file(const char *fileName, WAVFile *wavFile);

/* Print WAV file information to stdout */
void print_wav_info(const WAVFile *wavFile);

/* Free memory allocated for WAV data */
void free_wav_file(WAVFile *wavFile);

#endif /* WAV_PARSER_H */
