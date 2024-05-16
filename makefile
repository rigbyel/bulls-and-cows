all: main

main: main.o host.o solver.o
	g++ -O0 main.o host.o solver.o -lncurses -o main

main.o: main.cpp
	g++ -c main.cpp -lncurses

host.o: host.cpp
	g++ -c host.cpp -lncurses

solver.o: solver.cpp
	g++ -c solver.cpp -lncurses