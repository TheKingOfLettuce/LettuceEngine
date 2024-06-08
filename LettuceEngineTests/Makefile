rwildcard = $(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))
.PHONY: BuildTestExe clean

CXX = g++
CXXFLAGS = -Wall -g

SRC_DIR = src
SRC_FILES = $(call rwildcard, $(SRC_DIR), *.cpp)

BUILD_DIR = bin
OBJ_DIR = obj
INCLUDE_DIR = ../include
LIB_DIR = ../bin

EXE_NAME = Test.exe

OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))
DEP_FILES = $(OBJ_FILES:.o=.d)

BuildTestExe: $(OBJ_FILES)
	@mkdir -p $(dir $(BUILD_DIR)/)
	$(CXX) $(CXXFLAGS) $(OBJ_FILES) -I $(INCLUDE_DIR) -I include -L $(LIB_DIR) -lLettuceEngine -lraylib -lgdi32 -lwinmm -o $(BUILD_DIR)/$(EXE_NAME) -fuse-ld=lld

# Build object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I $(INCLUDE_DIR) -I include -MMD -c -o $@ $<

# Include headers
-include $(DEP_FILES)

# Clean
clean:
	rm -rf $(BUILD_DIR) $(OBJ_DIR)