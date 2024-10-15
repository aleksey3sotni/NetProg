
CXX = g++


CXXFLAGS = -Wall -g


LDLIBS = -lsocket -lnsl


CLIENT_OBJ = daytime_client.o
SERVER_OBJ = daytime_server.o


all: client server

client: $(CLIENT_OBJ)
    $(CXX) $(CXXFLAGS) $(CLIENT_OBJ) -o daytime_client $(LDLIBS)

server: $(SERVER_OBJ)
    $(CXX) $(CXXFLAGS) $(SERVER_OBJ) -o daytime_server $(LDLIBS)


$(CLIENT_OBJ): daytime_client.cpp
    $(CXX) $(CXXFLAGS) -c daytime_client.cpp

$(SERVER_OBJ): daytime_server.cpp
    $(CXX) $(CXXFLAGS) -c daytime_server.cpp


clean:
    rm -f *.o daytime_client daytime_server
