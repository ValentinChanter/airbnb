CC = gcc
CFLAGS = -W -Wall
LIBS = -lm
EXEC = airbnb

all: $(EXEC)

$(EXEC): airbnb.o main.o
	$(CC) -o $(EXEC) airbnb.o main.o $(CFLAGS) $(LIBS)

airbnb.o: airbnb.c airbnb.h
	$(CC) -o airbnb.o -c airbnb.c $(CFLAGS)

main.o: main.c airbnb.h
	$(CC) -o main.o -c main.c $(CFLAGS)

clean:
	rm -rf *.o