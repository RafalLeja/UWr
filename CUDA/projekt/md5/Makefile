# Compiler settings
CC      := gcc
NVCC    := nvcc

# Directories
SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin

# Target executable
TARGET := $(BIN_DIR)/app

# Flags
CFLAGS   := -O2 -Wall -Wextra -I$(SRC_DIR)
NVCCFLAGS := -O2 -lineinfo -I$(SRC_DIR)

# Source files
C_SOURCES  := $(wildcard $(SRC_DIR)/*.c)
CU_SOURCES := $(wildcard $(SRC_DIR)/*.cu)

# Object files
C_OBJECTS  := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(C_SOURCES))
CU_OBJECTS := $(patsubst $(SRC_DIR)/%.cu,$(BUILD_DIR)/%.o,$(CU_SOURCES))

# Dependency files
DEPS := $(C_OBJECTS:.o=.d) $(CU_OBJECTS:.o=.d)

# Default target
all: $(TARGET)

# Link step
$(TARGET): $(C_OBJECTS) $(CU_OBJECTS) | $(BIN_DIR)
	$(NVCC) $(NVCCFLAGS) -o $@ $^

# Compile C files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

# Compile CUDA files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cu | $(BUILD_DIR)
	$(NVCC) $(NVCCFLAGS) -MMD -MP -c $< -o $@

# Create build directories
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Include dependency files
-include $(DEPS)

# Clean
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: all clean

# CC = nvcc
# CFLAGS = -O2
# TARGET = ./build/md5
# SRCS := $(wildcard ./src/*.c) 
# OBJS = $(SRCS:.c=.o) 
#
# all: $(TARGET)
#
# $(TARGET): $(OBJS)
# 	$(CC) $(CFLAGS) -o $@ $^
#
# # $(OBJS): ./src/%.o : ./src/%.c
# # 	$(CC) $(CFLAGS) -c $< -o $@
#
# clean:
# 	rm -f $(TARGET) $(OBJS)

