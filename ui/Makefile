# Compiler
CC = gcc

# Libraries to link
LIBS = -lncurses

# Source files
SRCS = menuUI.c

# Object files
OBJS = $(SRCS:.c=.o)

# Executable name (no .c here!)
TARGET = menuUI

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LIBS)

# Compile .c files to .o files
%.o: %.c
	$(CC) -c $< -o $@

# Clean compiled files
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
