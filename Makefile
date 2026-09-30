CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic
TARGET = matrix_lab.exe
SOURCE = main.cpp

.PHONY: all

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) $(SOURCE) -o $(TARGET)