rwildcard = $(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))
.PHONY: BuildStaticLib clean

CXX = g++
CXXFLAGS = -Wall -g

SRC_DIR = src
SRC_FILES = $(call rwildcard,src,*.cpp)

BUILD_DIR = bin
OBJ_DIR = obj
INCLUDE_DIR = include
RAYLIB_DIR = raylib

LIB_NAME = LettuceEngine.lib

OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))
DEP_FILES = $(OBJ_FILES:.o=.d)
RAYLIB_FILES = $(patsubst $(RAYLIB_DIR)/%, $(BUILD_DIR)/%, $(wildcard $(RAYLIB_DIR)/*))

BuildStaticLib: $(BUILD_DIR)/$(LIB_NAME) $(RAYLIB_FILES)

# Copy raylib files to bin
$(BUILD_DIR)/%: $(RAYLIB_DIR)/%
	cp $< $@  

# Build Static Lib
$(BUILD_DIR)/$(LIB_NAME): $(OBJ_FILES)
	@mkdir -p $(dir $@)
	ar rcs $@ $^

# Build object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I $(INCLUDE_DIR) -MMD -c -o $@ $<

# Include headers
-include $(DEP_FILES)

# Clean
clean:
	rm -rf $(BUILD_DIR) $(OBJ_DIR)