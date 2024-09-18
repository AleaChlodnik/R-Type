# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++20 -IInclude
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# Source and build directories
SRC_DIR = Src
BUILD_DIR = build
TARGET = r-type_client  # Executable will be placed in the current directory

# Collect all .cpp files in the source directory
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Default target
all: $(TARGET)

# Rule to build the final executable
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# Rule to build object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

re: clean all

.PHONY: all clean re
