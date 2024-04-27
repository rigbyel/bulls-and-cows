all: main clean

main: main.o host.o solver.o
	g++ main.o host.o solver.o -o main

main.o: main.cpp
	g++ -c main.cpp -o main.o

host.o: host.cpp
	g++ -c host.cpp -o host.o

solver.o: solver.cpp
	g++ -c solver.cpp -o solver.o

clean:
	rm -rf *.o
	rm -rf main