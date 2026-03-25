# Compiler
CC = g++

# Compiler flags
CFLAGS = -g -Wall -std=c++11

# Include directory
INCLUDE = .

# Source files
SOURCES = hierarchy_functions.cpp interface.cpp main.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Executable name
EXECUTABLE = main

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -I$(INCLUDE) $^ -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE) 