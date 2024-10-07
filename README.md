## open_audio_c: A Lightweight, Fast, and Modular CLI Audio Processing Tool

### Overview
**open_audio_c** is a highly optimized, modular, and command-line-friendly audio processing tool designed for fast, scalable, and customizable workflows. Whether you’re dealing with simple audio conversions or complex real-time audio pipelines, **open_audio_c** offers a low-latency, lightweight alternative to heavy audio frameworks.

Built from the ground up with a **CLI-first approach**, this tool focuses on high performance, minimal overhead, and extreme flexibility. It allows users to process audio through highly customizable chains of modules, making it ideal for a wide variety of use cases.

---

### Key Features:
- **Wicked fast**: Optimized for speed, with support for in-memory and real-time processing.
- **Modular**: Each audio processing function (e.g., normalization, filtering, effects) is built as a separate module, enabling highly customizable processing chains.
- **Lightweight**: Minimal system resource usage makes it perfect for constrained environments (e.g., embedded systems, servers).
- **CLI-friendly**: Fully operable from the command line, ideal for batch processing and automation.
- **Scalable**: Easily scales to handle large projects and can be extended to support additional audio formats and processors.
- **Piping Support**: Uses Unix-style piping to connect modules without intermediate files, reducing disk I/O overhead.

---

### When to Use **open_audio_c** Instead of Other Frameworks (e.g., Audacity):

1. **CLI-first Automation and Scriptability**:
   - **open_audio_c** is designed to be fully **command-line driven**, making it ideal for users who need to automate audio tasks or script complex audio processing pipelines. While **Audacity** offers limited CLI support, it’s primarily GUI-based, making it less suited for full CLI workflows.
   - **Use Case**: Running automated audio conversions, normalization, and filtering across large batches of audio files in a headless environment.

2. **Low-latency, Real-time Processing**:
   - If you need **real-time, low-latency** audio processing (e.g., for live performances, audio streaming, or embedded systems), **open_audio_c** offers a minimal overhead solution with optimizations for in-memory processing.
   - **Use Case**: Live sound processing, or real-time DSP (Digital Signal Processing) tasks where speed is critical.

3. **Modular and Scalable Audio Processing Pipelines**:
   - **open_audio_c** breaks down audio processing into **modular components** that can be chained together, making it highly customizable for a variety of workflows. Each component is optimized for a specific task (e.g., filtering, normalization) and can be reused across pipelines. In contrast, frameworks like Audacity are monolithic and require scripting knowledge for advanced tasks.
   - **Use Case**: Complex audio processing pipelines, where users need flexibility in chaining different audio effects, normalization, and filters.

4. **Lightweight and Embedded Systems**:
   - If you’re working in **constrained environments** (e.g., embedded systems, IoT devices), **open_audio_c** is designed to use minimal system resources, unlike heavy frameworks like Audacity. This makes it perfect for processing audio on devices with limited memory or CPU power.
   - **Use Case**: Embedded audio processing for hardware devices (e.g., Raspberry Pi), or environments where resource efficiency is key.

5. **Batch Processing and Server-side Audio**:
   - **open_audio_c** shines in environments where large numbers of audio files need to be processed quickly, without the overhead of a GUI. Its **CLI-first design** allows it to be easily integrated into server-side batch processing systems, custom audio render farms, or production pipelines.
   - **Use Case**: Server-based audio rendering or production environments where scripts and automation are key, such as game development or post-production.

---

### Installation and Usage

```bash
git clone https://github.com/CamKHardin/open_audio_c.git
cd open_audio_c
make
