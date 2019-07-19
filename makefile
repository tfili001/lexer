lexer: main.o tokenizer.o parser.o
	g++ main.o parser.o -o lexer

main.o: main.cpp 
	g++ -c main.cpp

tokenizer.o: tokenizer.cpp token.h
	g++ -c tokenizer.cpp

parser.o: parser.cpp enviroment.h
	g++ -c parser.cpp


