# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++11
INC := -I.

# Source files
SRCS := main.cpp Lexer.cpp Token.cpp ./utils/utils.cpp

# Object files
OBJS := $(SRCS:.cpp=.o)

# Output executable
TARGET := main

# Build rule
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INC) -c $< -o $@

# Clean rule
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
