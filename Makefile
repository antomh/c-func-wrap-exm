CC=gcc
CFLAGS=-c -Wall
#--------------------------------------
GL_NAME=main # GoaL of the building
LB_NAME=cdl # Custom DLopen -> cdl

all: clean main

#--------------------------------------

lib_cdlopen: libcdl.c
	@if test -e libcdl.so ; then rm libcdl.so 2>/dev/null ; fi
	$(CC) -g -Wall -shared -fPIC -o libcdl.so libcdl.c -ldl

# В аргументах -ldl должен строго после ./libcdl.so, так как этот
# порядок определяет включение библиотек.
exe_main:
	gcc -o $(GL_NAME) main.c ./libcdl.so -ldl

#--------------------------------------

clean:
	rm -rf *.o *.so ccrc icon main