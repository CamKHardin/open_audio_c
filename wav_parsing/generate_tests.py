import wave
import struct
import os

# Directory to store generated test files
output_dir = "tests"
if not os.path.exists(output_dir):
    os.makedirs(output_dir)

# List of bit depths, sample rates, and channels to test
bit_depths = [8, 16, 24, 32]
sample_rates = [11025, 22050, 44100, 48000, 96000, 192000]
channels = [1, 2]  # Mono and Stereo

# Generate audio data (simple sine wave or noise) for valid files
def generate_audio_data(duration, sample_rate, num_channels, bit_depth):
    num_frames = duration * sample_rate
    max_amplitude = 2**(bit_depth - 1) - 1
    audio_data = []

    # Generate basic audio (simple repeating pattern)
    for i in range(int(num_frames)):
        value = max_amplitude * (i % 2)  # Alternating pattern
        for _ in range(num_channels):
            audio_data.append(value)

    # Pack the audio data according to bit depth
    if bit_depth == 8:
        packed_data = struct.pack(f'<{len(audio_data)}B', *[(int(x) & 0xFF) for x in audio_data])
    elif bit_depth == 16:
        packed_data = struct.pack(f'<{len(audio_data)}h', *audio_data)
    elif bit_depth == 24:
        packed_data = b''.join([struct.pack('<i', int(x))[1:4] for x in audio_data])
    elif bit_depth == 32:
        packed_data = struct.pack(f'<{len(audio_data)}i', *audio_data)
    
    return packed_data

# Write a valid WAV file with the given parameters
def write_valid_wav(file_name, sample_rate, num_channels, bit_depth, duration=1):
    file_path = os.path.join(output_dir, file_name)
    with wave.open(file_path, 'wb') as wav_file:
        wav_file.setnchannels(num_channels)
        wav_file.setsampwidth(bit_depth // 8)
        wav_file.setframerate(sample_rate)
        audio_data = generate_audio_data(duration, sample_rate, num_channels, bit_depth)
        wav_file.writeframes(audio_data)

# Create all valid WAV files
def generate_valid_wav_files():
    for bit_depth in bit_depths:
        for sample_rate in sample_rates:
            for channel_count in channels:
                file_name = f"valid_{bit_depth}bit_{'mono' if channel_count == 1 else 'stereo'}_{sample_rate}.wav"
                write_valid_wav(file_name, sample_rate, channel_count, bit_depth)

# Create an invalid WAV file by writing corrupt headers or truncating data
def write_invalid_wav(file_name, corrupt_header=False, truncate=False):
    file_path = os.path.join(output_dir, file_name)
    with wave.open(file_path, 'wb') as wav_file:
        wav_file.setnchannels(2)  # Stereo
        wav_file.setsampwidth(2)  # 16-bit
        wav_file.setframerate(44100)

        # Create audio data
        audio_data = generate_audio_data(1, 44100, 2, 16)
        
        if not truncate:
            wav_file.writeframes(audio_data)

        # If truncating, write only part of the data
        if truncate:
            wav_file.writeframes(audio_data[:len(audio_data)//2])

    # Corrupt the header manually (if needed)
    if corrupt_header:
        with open(file_path, 'r+b') as f:
            f.seek(0)
            f.write(b"FAKE")  # Corrupting the "RIFF" header

# Generate invalid files (corrupt headers, truncated data, etc.)
def generate_invalid_wav_files():
    # Corrupt header (invalid "RIFF")
    write_invalid_wav("invalid_corrupt_header.wav", corrupt_header=True)

    # Truncated data
    write_invalid_wav("invalid_truncated_data.wav", truncate=True)

    # Non-PCM format (not supported in the basic wave library, so would need hex editor)

    # Zero data size (create an empty data chunk)
    empty_wav_file = os.path.join(output_dir, "invalid_zero_data_size.wav")
    with wave.open(empty_wav_file, 'wb') as wav_file:
        wav_file.setnchannels(2)  # Stereo
        wav_file.setsampwidth(2)  # 16-bit
        wav_file.setframerate(44100)
        wav_file.writeframes(b'')  # No audio data

    # Invalid "fmt " chunk (requires a hex editor to change manually)

# Run all generators
if __name__ == "__main__":
    generate_valid_wav_files()
    generate_invalid_wav_files()
    print("All test WAV files generated.")