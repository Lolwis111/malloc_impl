#!/usr/bin/make

# Flags
CFLAGS = -Wall -Werror -Wpedantic -g -Og
LDFLAGS = 

# Find all C files in the current directory
SRC = $(wildcard *.c)

# Object files
OBJ = $(SRC:.c=.o)

# Output executable name
EXE = c_malloc_test

# Default target: compile and link
all: $(EXE)

# Link the object files into the final executable
$(EXE): $(OBJ)
	$(CC) $(LDFLAGS) -o $(EXE) $(OBJ)

# Rule to compile .c files to .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -f $(OBJ) $(EXE)

# Phony targets (not actual files)
.PHONY: all clean