CC=g++
CFLAGS=-c -g -Wall -std=c++0x
LDFLAGS=
SOURCES=cpMap.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=cpMap

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
