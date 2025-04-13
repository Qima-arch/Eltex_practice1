CC = gcc
CFLAGS = -Wall -Wextra
TARGET = area_counter
SOURCE = main.c

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(TARGET) *.o

rebuild: clean all

.PHONY: all clean rebuild