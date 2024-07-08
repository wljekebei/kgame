# variables
CC=gcc
CFLAGS=-std=c11 -Wall -Werror -Wno-vla-parameter
LDLIBS=-lm -lcurses
OUTPUT=k

# targets
all: $(OUTPUT)

$(OUTPUT): k.o hof.o main.o
	cppcheck --enable=performance --error-exitcode=1 *.c
	$(CC) $(CFLAGS) k.o hof.o main.o $(LDLIBS) -o $(OUTPUT)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c $(LDLIBS) -o main.o

k.o: k.c k.h
	$(CC) $(CFLAGS) -c k.c $(LDLIBS) -o k.o

hof.o: hof.c hof.h
	$(CC) $(CFLAGS) -c hof.c $(LDLIBS) -o hof.o

# remove compiled files
clean: 
	rm -rf $(OUTPUT) *.o
