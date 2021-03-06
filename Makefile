DEBUG = -g
OPTS = $(DEBUG) -std=c++20 -Wall -ansi -pedantic

CC=g++ $(OPTS) -c
LN=g++

runMe: main.o AirportAnimator.o
	$(LN) -o runMe main.o AirportAnimator.o -lncurses -lpthread

main.o: main.cpp AirportAnimator.hpp
	$(CC) main.cpp

AirportAnimator.o: AirportAnimator.cpp AirportAnimator.hpp
	$(CC) AirportAnimator.cpp


