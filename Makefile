#simple makefile to make my job here easier

OBJECTS = main.o string_processing.o
SOURCES = main.cpp string_processing.cpp
EXECUTABLES = main

all : build

build: $(OBJECTS)
	g++ $(OBJECTS) -o main

$(OBJECTS): $(SOURCES)
	g++ $(SOURCES) -c

clean:
	rm $(OBJECTS) $(EXECUTABLES)

