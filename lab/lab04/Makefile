#
# CIS330: Lab 3
#
# Makefile to build libraries and test applications.
#

CC=gcc
AR=ar

CFLAGS=-g -O2 -I./include -L./lib
LIBS=-llab4 -lm

all: lab4

obj:
	mkdir -p obj

lib:
	mkdir -p lib

obj/stats.o: src/stats.c include/stats.h obj
	$(CC) $(CFLAGS) -c -o $@ $<

obj/ohno.o: src/ohno.c include/ohno.h obj
	$(CC) $(CFLAGS) -c -o $@ $<

lib/liblab4.a: obj/stats.o obj/ohno.o lib
	$(AR) rc lib/liblab4.a obj/stats.o obj/ohno.o

lab4_dyn: obj/stats.o obj/ohno.o lib
	$(CC) -shared obj/shared/stats.o obj/shared/ohno.o -o obj/shared/liblab4.so
	$(CC) obj/lab4 -Lobj/shared -llab4 -o -obj/use-shared-library
	LD_LIBRARY_PATH=$(pwd)/obj/shared obj/use-shared-library
	sudo mv obj/shared/liblab4.so /lab04
	sudo chmod 755 /lab04/liblab4.so
	obj/use-shared-library




lab4: src/lab4.c lib/liblab4.a
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

clean:
	rm lab4 lib/liblab4.a obj/ohno.o obj/stats.o
	rmdir obj
	rmdir lib
