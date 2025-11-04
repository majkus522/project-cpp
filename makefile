CXX := g++

SRC_DIR := source
BUILD_DIR := build
TARGET := sfml-app

CPP_FILES := $(shell find $(SRC_DIR) -type f -name '*.cpp')
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(CPP_FILES))

.PHONY: all clean

all: $(BUILD_DIR) $(TARGET)

$(TARGET): $(OBJ_FILES)
	@echo "Linking object files into $(TARGET)..."
	@$(CXX) $(OBJ_FILES) -o $(TARGET) -lsfml-graphics -lsfml-window -lsfml-system
	@echo "All object files:"
	@echo $(OBJ_FILES) | xargs

$(BUILD_DIR):
	@echo "Creating build directory..."
	@mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "Compiling $< -> $@"
	@mkdir -p $(dir $@)
	@$(CXX) -c $< -o $@

clean:
	@echo "Cleaning up build directory..."
	@rm -rf $(BUILD_DIR)
	@rm -rf sfml-app