#Thanks to https://www.matansilver.com/2017/08/29/universal-makefile/

CC = gcc

TARGET_EXEC ?= JEngine
BUILD_DIR ?= bin
SRC_DIRS ?= src lib

#Thanks to https://stackoverflow.com/a/18258352
rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

SRCS := $(call rwildcard,$(SRC_DIRS),*.cpp *.c)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

CFLAGS   = -I./src -I. -I./lib -O0 -g3
CXXFLAGS = -std=c++14

#if shared library target
#CFLAGS += -shared -undefined dynamic_lookup

#Windows
#ifdef _WIN32
LDFLAGS = -lgdi32 -lopengl32
#endif
#Linux
#ifdef __linux__
#LDFLAGS = -lX11 -lGL
#endif

# main target (C++)
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# c source
$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CFLAGS) $(CXXFLAGS) -c $< -o $@


.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)


MKDIR_P ?= mkdir -p

.PHONY: run
run: $(BIN)
	./$(BUILD_DIR)/$(TARGET_EXEC)