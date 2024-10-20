# Compiler and flags
CC = gcc
CFLAGS = -Wall -fPIC -I./include -I/usr/local/include
LDFLAGS = -shared -lGL -lSDL2

# Output shared library
LIBNAME = libgame3d.so
BUILD_LIB = $(BUILDDIR)/$(LIBNAME)

# Source and build directories
SRCDIR = src
BUILDDIR = build

# Recursively find all .c files
SRCS = $(shell find $(SRCDIR) -name '*.c')

# Convert source paths to object paths (placing them in the build directory)
OBJS = $(SRCS:$(SRCDIR)/%.c=$(BUILDDIR)/%.o)

# Default target: build the shared library
all: $(BUILD_LIB)

# Create the shared library inside the build directory
$(BUILD_LIB): $(OBJS)
	@mkdir -p $(BUILDDIR)  # Ensure the build directory exists
	$(CC) $(LDFLAGS) -o $@ $(OBJS)

# Rule to compile each .c file into a .o file in the build directory
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)  # Create necessary directories for object files
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target: remove build directory and shared library
clean:
	rm -rf $(BUILDDIR)

.PHONY: all clean
