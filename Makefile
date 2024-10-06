CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = wav_parser
SRC = src/wav_parser.c src/main.c
INCLUDES = -Iinclude

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(INCLUDES) -o $(TARGET)

clean:
	rm -f $(TARGET)
