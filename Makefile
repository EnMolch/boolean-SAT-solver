#simple makefile to make my job here easier

OBJECTS = main.o string_processing.o input_handler.o linked_list.o
SOURCES = main.cpp string_processing.cpp input_handler.cpp linked_list.cpp
EXECUTABLES = main

all : build

build: $(OBJECTS)
	g++ $(OBJECTS) -o main

$(OBJECTS): $(SOURCES)
	g++ $(SOURCES) -c

clean:
	rm $(OBJECTS) $(EXECUTABLES)

