# This is a comment line
CC=g++
# CFLAGS will be the options passed to the compiler
CFLAGS=-c -Wall

all: lab_11

lab_11: lab_11.o
	$(CC) lab_11.o -o lab_11

lab_11.o: lab_11.cpp
	$(CC) $(CFLAGS) lab_11.cpp

clean:
	rm -rf *.o lab_11