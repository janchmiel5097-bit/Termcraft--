# flags
CXX      := g++
# remove -g for release
CXXFLAGS := -std=c++17 -Wall -Wextra -g -Ithirdparty/glad/include

# libs
LIBS     := -lglfw -lGL

# dirs
SRC_DIR      := src
GLAD_SRC_DIR := thirdparty/glad/src
BUILD_DIR    := build

# sources
SRC  := $(SRC_DIR)/main.cpp $(GLAD_SRC_DIR)/glad.c
OBJ  := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(filter %.cpp,$(SRC))) \
        $(patsubst %.c,$(BUILD_DIR)/%.o,$(filter %.c,$(SRC)))

# target
TARGET := $(BUILD_DIR)/main

# def target
all: $(BUILD_DIR) $(TARGET)

# link
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LIBS)

# C++ sources
$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# C sources
$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# build dir exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# clean
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

# run = clean, build, execute
.PHONY: run
run: clean all
	$(TARGET)
