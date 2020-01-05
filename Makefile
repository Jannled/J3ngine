#Thanks to https://www.matansilver.com/2017/08/29/universal-makefile/

TARGET_EXEC ?= JEngine
BUILD_DIR ?= bin
SRC_DIRS ?= src lib

SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

CFLAGS   = -I. -O0 -g3
CXXFLAGS = -std=c++14

#if shared library target
#CFLAGS += -shared -undefined dynamic_lookup

#Windows
#LDFLAGS = -lgdi32 -lopengl32

#Linux
LDFLAGS = -lX11 -lGL

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