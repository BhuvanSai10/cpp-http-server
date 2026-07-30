CXX = g++
CXXFLAGS = -std=c++17 -Wall -pthread -Iinclude

SERVER = server
CLIENT = client

all: $(SERVER) $(CLIENT)

$(SERVER):
	$(CXX) $(CXXFLAGS) \
	src/server.cpp \
	src/parser.cpp \
	src/router.cpp \
	src/file_reader.cpp \
	src/mime_type.cpp \
	-o $(SERVER)

$(CLIENT):
	$(CXX) $(CXXFLAGS) \
	src/client.cpp \
	-o $(CLIENT)

clean:
	rm -f $(SERVER) $(CLIENT)