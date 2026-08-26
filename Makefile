#Variables
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude
TARGET = spinningObjects

SRCS = src/main.cpp src/customMathLib.cpp src/renderer.cpp
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

#Link object files to make final exe
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

#Compile
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

#Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)