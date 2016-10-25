FLAGS = -g -Wall -O2

PROG = out

LEXICAL_FILE = lexical.l
PARSER_FILE = syntactic.s
STRUCT_FILE = struct_manipulation.c

LEXICAL_OUTPUT = lex.yy.c 
PARSER_OUTPUT = y.tab.c

LEXICAL_HEADER = lexical.h
PARSER_HEADER = y.tab.h
STRUCT_HEADER = struct_manipulation.h
TREE_HEADER = tree_structure.h

LEXICAL_OBJECT = lex.yy.o
PARSER_OBJECT = y.tab.o
STRUCT_OBJECT = struct_manipulation.o



OBJECTS = $(PARSER_OBJECT) $(LEXICAL_OBJECT) $(STRUCT_OBJECT)

TO_REMOVE = $(OBJECTS) $(LEXICAL_OUTPUT) $(PARSER_OUTPUT) $(PARSER_HEADER) y.output

C = gcc

$(PROG) : $(OBJECTS)
	$(C) -o $(PROG) $(OBJECTS) $(FLAGS)

$(PARSER_OBJECT) : $(PARSER_OUTPUT) $(LEXICAL_HEADER) $(STRUCT_HEADER) $(TREE_HEADER)
	$(C) -o $(PARSER_OBJECT) -c $(PARSER_OUTPUT) $(FLAGS) 

$(LEXICAL_OBJECT) : $(LEXICAL_OUTPUT) $(LEXICAL_HEADER)
	$(C) -o $(LEXICAL_OBJECT) -c $(LEXICAL_OUTPUT) $(FLAGS)

$(STRUCT_OBJECT) : $(STRUCT_FILE) $(STRUCT_HEADER) $(TREE_HEADER)

$(LEXICAL_OUTPUT) : $(LEXICAL_FILE)
	lex $(LEXICAL_FILE)

$(PARSER_OUTPUT) : $(PARSER_FILE)
	yacc -d -v -t $(PARSER_FILE)

run: $(PROG)
	./$(PROG)

clean:
	rm $(TO_REMOVE)