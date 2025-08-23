# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -O2 -g -I. -I./cJSON

# Libraries to link
LIBS = -lcurl -lssl -lcrypto -luuid -lncurses

# Directories
OBJ_DIR = obj
BIN_DIR = bin

# Source files (explicitly list all .c files)
SRCS = main.c translateMode.c utils.c saved.c history.c apiRequest.c \
       parser.c requestBuilder.c errors.c welcomePage.c menuPage.c ascii.c

# Object files for main sources
OBJS = $(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))

# Add cJSON object
OBJS += $(OBJ_DIR)/cJSON.o

# Executable
TARGET = $(BIN_DIR)/main

# Default target
all: $(OBJ_DIR) $(BIN_DIR) $(TARGET)

# Link objects into final binary
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

# Compile .c -> .o for files in current directory
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Special rule for cJSON
$(OBJ_DIR)/cJSON.o: cJSON/cJSON.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create directories if missing
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Clean build
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Install dependencies (for Ubuntu/Debian)
install-deps:
	sudo apt update
	sudo apt install -y libncurses5-dev libcurl4-openssl-dev libssl-dev uuid-dev

# Check if all source files exist
check-sources:
	@echo "Checking source files..."
	@for src in $(SRCS); do \
		if [ ! -f "$$src" ]; then \
			echo "ERROR: Source file $$src not found!"; \
			exit 1; \
		fi; \
	done
	@echo "All source files found!"

.PHONY: all clean install-deps check-sources

