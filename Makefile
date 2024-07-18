#Makefile
all: addnbo

addnbo: main.o
	g++ -o addnbo main.o

main.o: main.cpp
	g++ -c -o main.o main.cpp

clean:
	rm -f addnbo
	rm -f *.o

