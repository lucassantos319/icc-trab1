DEPS = utils.h

CC = gcc

CFLAGS = -Wall -I/usr/local/include 

LFLAGS = -L/usr/local/lib -lmatheval

all: newton

newton: main.o functions.o utils.o
	$(CC) -o newtonPC main.o functions.o  utils.o $(LFLAGS)

functions.c: functions.h
utils.c: utils.h

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $< 

clean:
	-rm -f *~ *\# \#* *.o newtonPC

purge: clean
	-rm -f newtonPC

