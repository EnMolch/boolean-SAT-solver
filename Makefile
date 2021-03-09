#simple makefile to make my job here easier

OBJECTS = main.o string_processing.o input_handler.o linked_list.o stack.o parser.o syntax_tree.o evaluator.o lexer.o
SOURCES = main.cpp string_processing.cpp input_handler.cpp linked_list.cpp stack.cpp parser.cpp syntax_tree.cpp evaluator.cpp lexer.cpp
EXECUTABLES = main

all : main

main: $(OBJECTS)
	g++ $(OBJECTS) -o main -ggdb

$(OBJECTS): $(SOURCES)
	g++ $(SOURCES) -c

clean:
	rm $(OBJECTS) $(EXECUTABLES)

