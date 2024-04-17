all: main clean

main: main.o host.o
	g++ main.o host.o -o main

main.o: main.cpp
	g++ -c main.cpp -o main.o

host.o: host.cpp
	g++ -c host.cpp -o host.o

clean:
	rm -rf *.o