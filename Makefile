CC := gcc
CFLAGS := -g -Wall -Wno-deprecated-declarations -Werror

all: gcc SEEsh.c -o SEEsh

SEEsh: SEEsh.c
	gcc -Wall SEEsh.c -Werror -o SEEsh

clean:
	-rm -rf *.o *.exe
