# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -O2 -g -I./headers -I./cJSON

# Libraries
LIBS = -lcurl -lssl -lcrypto -luuid -lncurses

# Directories
OBJ_DIR = obj
BIN_DIR = bin

# Source files
SRCS = main.c translateMode.c utils.c saved.c history.c apiRequest.c \
       parser.c requestBuilder.c errors.c welcomePage.c menuPage.c ascii.c cJSON/cJSON.c

# Object files (all go into obj/, no nested folders)
OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(filter-out cJSON/cJSON.c,$(SRCS))) $(OBJ_DIR)/cJSON.o

# Executable
TARGET = $(BIN_DIR)/main

# Default target
all: $(OBJ_DIR) $(BIN_DIR) $(TARGET)

# Link executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

# Compile normal .c files -> obj/
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile cJSON.c -> obj/cJSON.o
$(OBJ_DIR)/cJSON.o: cJSON/cJSON.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create directories if missing
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Clean everything
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean
