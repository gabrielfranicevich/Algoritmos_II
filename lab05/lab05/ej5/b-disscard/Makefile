CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99 -g
SOURCES = queue.c queue_helpers.c main.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = queue

$(TARGET): $(OBJECTS)
	gcc $(CFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.c
	gcc $(CFLAGS) -c $<

debug: $(TARGET)
	gdb $(TARGET)

valgrind: $(TARGET)
	valgrind --leak-check=yes ./$(TARGET)

clean:
	rm -f $(OBJECTS) $(TARGET)