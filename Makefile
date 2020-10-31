all: 1m-block

1m-block: main.o oneMillionNetfilter.o 
	g++ -o 1m-block main.o oneMillionNetfilter.o -lnetfilter_queue

main.o: main.cpp 
	g++ -Wall -c -o main.o main.cpp 

oneMillionNetfilter.o: oneMillionNetfilter.cpp oneMillionNetfilter.h
	g++ -Wall -c -o oneMillionNetfilter.o oneMillionNetfilter.cpp

clean:
	rm -f 1m-block *.o
