CC = g++
CFLAGS = -Wall -g
PROG = echo_client
SOURCES = echo_client.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(PROG)

$(PROG): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(PROG) $(OBJECTS)
