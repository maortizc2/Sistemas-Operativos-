CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

OBJS = main.o huffman.o
TARGET = compressor

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp huffman.h
	$(CXX) $(CXXFLAGS) -c main.cpp

huffman.o: huffman.cpp huffman.h
	$(CXX) $(CXXFLAGS) -c huffman.cpp

clean:
	rm -f $(TARGET) $(OBJS)

