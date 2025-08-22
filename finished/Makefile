# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -O2 -g -Iinclude -I./cJSON

# Libraries to link
LIBS = -lcurl -lssl -lcrypto -luuid -lncurses

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Source files (all .c in src/ + cJSON)
SRCS = $(wildcard *.c) cJSON/cJSON.c


# Object files (map .c -> obj/*.o)
OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))

# Dependency files
DEPS = $(OBJS:.o=.d)

# Executable
TARGET = $(BIN_DIR)/main

# Default target
all: $(OBJ_DIR) $(BIN_DIR) $(TARGET)

# Link objects into final binary
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

# Compile .c -> .o (with auto dependency generation)
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@


# Include dependency files if they exist
-include $(DEPS)

# Create directories if missing
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Clean build
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean

