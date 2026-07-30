CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude

SERVER_SRC = \
	src/server.cpp \
	src/parser.cpp \
	src/router.cpp \
	src/file_reader.cpp \
	src/mime_type.cpp \
	src/http_response.cpp

CLIENT_SRC = src/client.cpp

all: server client

server:
	$(CXX) $(CXXFLAGS) $(SERVER_SRC) -o server

client:
	$(CXX) $(CXXFLAGS) $(CLIENT_SRC) -o client

clean:
	rm -f server client

run:
	./server

.PHONY: all clean run