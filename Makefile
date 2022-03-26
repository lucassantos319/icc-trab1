all:
	gcc -Wall utils.c functions.c main.c -I/usr/local/include -L/usr/local/lib -lmatheval
