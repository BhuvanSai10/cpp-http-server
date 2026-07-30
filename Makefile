CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

TARGET = server
SOURCE = server.cpp

all:
	$(CXX) $(CXXFLAGS) $(SOURCE) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)