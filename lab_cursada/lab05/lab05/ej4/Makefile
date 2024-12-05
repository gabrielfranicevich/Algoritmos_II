CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99 -g
SOURCES = stack.c hanoi.c main.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = solve-hanoi

.PHONY: clean run val

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(LFLAGS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJECTS) $(TARGET)

#
run: all
	@./solve-hanoi $(filter-out $@,$(MAKECMDGOALS))

val: all
	@valgrind --leak-check=full ./solve-hanoi $(filter-out $@,$(MAKECMDGOALS))

%:
	@: