CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99 -g
SOURCES = dict_helpers.c dict.c helpers.c string.c main.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = dictionary

.PHONY: clean read val

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(LFLAGS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJECTS) $(TARGET)

#
dict: all
	@./$(TARGET) $(filter-out $@,$(MAKECMDGOALS))

val: all
	@valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET) $(filter-out $@,$(MAKECMDGOALS))

%:
	@:
