<<<<<<< HEAD
# open_audio_c
A C audio library
=======
# WAV File Parser

## Overview

This project provides a robust, modular, and highly optimized C program for parsing WAV files. It reads essential information from a WAV file and provides the raw audio data for further processing.

### Features

- Support for PCM WAV files (uncompressed).
- Modular design with separate header and source files.
- Provides error handling and memory management.
- Suitable for production environments and reusable in other projects.

## Input/Output Description

### Input:

- **WAV File**: The parser accepts a WAV file as input. The file must be in uncompressed PCM format, but it can have any bit depth (e.g., 8-bit, 16-bit, 24-bit) and any sample rate (e.g., 44.1 kHz, 48 kHz).

### Output:

- The parser produces a **`WAVFile` structure** containing:
  - **Header Information**:
    - `riff`: The "RIFF" identifier for the file.
    - `chunkSize`: The size of the file minus 8 bytes.
    - `wave`: The "WAVE" identifier.
  - **Format Information** (`fmtChunk`):
    - `audioFormat`: The audio format (1 for PCM).
    - `numChannels`: Number of audio channels (1 = mono, 2 = stereo).
    - `sampleRate`: The sample rate in Hz (e.g., 44100 for CD quality).
    - `bitsPerSample`: The number of bits per sample (e.g., 16-bit or 24-bit).
    - `byteRate`: The byte rate (calculated as `sampleRate * numChannels * bitsPerSample / 8`).
    - `blockAlign`: Block alignment (calculated as `numChannels * bitsPerSample / 8`).
  - **Audio Data**:
    - `dataSize`: The size of the audio data in bytes.
    - `audioData`: A pointer to dynamically allocated memory containing the raw audio samples. The format of the samples depends on the `bitsPerSample` and `numChannels` fields.

### Example I/O Flow:

1. **Input**: WAV file (e.g., `input.wav`)
   - Can have any bit depth (e.g., 16-bit, 24-bit), sample rate (e.g., 44.1kHz, 48kHz), and number of channels (mono, stereo).
2. **Output**:
   - Struct `WAVFile`:
     - **Header Information**:
       - `riff = "RIFF"`
       - `chunkSize = X bytes`
       - `wave = "WAVE"`
     - **Format Information** (`fmtChunk`):
       - `audioFormat = 1 (PCM)`
       - `numChannels = 2 (Stereo)`
       - `sampleRate = 44100 Hz`
       - `bitsPerSample = 16`
     - **Data Information** (`dataChunk`):
       - `dataSize = X bytes`
       - `audioData`: Pointer to dynamically allocated buffer holding the raw audio samples.

## How to Access and Use the Audio Data

The audio data is stored in the `audioData` field of the `WAVFile` struct, as a dynamically allocated array of raw audio samples. Here's how you can access and manipulate the audio data:

### Extracting Audio Data:

If the WAV file is stereo with 16-bit samples, the data is stored as an array of `int16_t` values, where:

- Odd indices represent the left channel.
- Even indices represent the right channel.

#### Example:

```c
for (uint32_t i = 0; i < (wavFile.dataChunk.dataSize / wavFile.fmtChunk.blockAlign); ++i) {
    int16_t leftChannel = wavFile.audioData[i * 2];
    int16_t rightChannel = wavFile.audioData[i * 2 + 1];
    // Process left and right channels here
}
```
>>>>>>> 29225da (Added WAV test files and WAV parser project)
