CC=gcc
CFLAGS=-std=c99

all: base opt

base: TestBase.o
        $(CC) -o base TestBase.o

opt: TestFast.o
        $(CC) -o opt TestFast.o

.PHONY: clean

clean:
        rm *.o
