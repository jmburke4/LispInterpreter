# Define source and binary directories
SRC_DIR = src
INC_DIR = include
BIN_DIR = bin

# Define the C compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I$(INC_DIR) -g

# Find all C source files in the source directory
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Generate corresponding object file names in the binary directory
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%.o,$(SRCS))

# Define the executable name
TARGET = $(BIN_DIR)/a

.PHONY: all clean

# Default target: build the executable
all: $(TARGET)

# Rule to create the binary directory if it doesn't exist
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Rule to link object files into the executable
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJS) -o $@

# Rule to compile C source files into object files
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target: remove generated files
clean:
	rm -f $(BIN_DIR)/*.o $(TARGET)
	rmdir $(BIN_DIR) 2>/dev/null || true
