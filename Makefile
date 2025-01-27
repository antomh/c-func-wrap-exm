CC=gcc
CFLAGS=-c -Wall
#--------------------------------------
GL_NAME=main
LB_NAME=cdl # Custom DLopen -> cdl

all: clean main

#--------------------------------------

lib_cdlopen: libcdl.c
	@if test -e libcdl.so ; then rm libcdl.so 2>/dev/null ; fi
	$(CC) -g -Wall -shared -fPIC -o libcdl.so libcdl.c -ldl

exe_main:
	gcc -o main main.c ./libcdl.so -ldl

#--------------------------------------

clean:
	rm -rf *.o *.so ccrc icon main