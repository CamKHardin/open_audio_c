#include <stdio.h>
#include <stdlib.h>
#include "wav_parser.h"

int main(int argc, char *argv[]) {
    WAVFile wavFile;
    int result;

    /* Ensure correct number of arguments */
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <wav_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Initialize WAVFile structure */
    wavFile.audioData = NULL;

    /* Parse WAV file */
    result = parse_wav_file(argv[1], &wavFile);
    if (result != WAV_SUCCESS) {
        free_wav_file(&wavFile);
        return EXIT_FAILURE;
    }

    /* Print WAV file information */
    print_wav_info(&wavFile);

    /* Clean up */
    free_wav_file(&wavFile);
    
    return EXIT_SUCCESS;
}
