CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99 -g
SOURCES = abb.c main.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = readtree

.PHONY: clean read val

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(LFLAGS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJECTS) $(TARGET)

#
read: all
	@./$(TARGET) $(filter-out $@,$(MAKECMDGOALS))

val: all
	@valgrind --leak-check=full ./$(TARGET) $(filter-out $@,$(MAKECMDGOALS))

%:
	@:
