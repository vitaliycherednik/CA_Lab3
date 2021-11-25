build: main.o
	g++ -o program main.o

main.o:
	g++ -c main.cpp

clean:
	rm -f main.o program