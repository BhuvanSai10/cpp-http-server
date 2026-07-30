CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude

SERVER = server
CLIENT = client

all: $(SERVER) $(CLIENT)

$(SERVER):
	$(CXX) $(CXXFLAGS) \
	src/server.cpp \
	src/parser.cpp \
	src/router.cpp \
	-o $(SERVER)

$(CLIENT):
	$(CXX) $(CXXFLAGS) \
	src/client.cpp \
	-o $(CLIENT)

clean:
	rm -f $(SERVER) $(CLIENT)