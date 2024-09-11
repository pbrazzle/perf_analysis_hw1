CC=gcc
CFLAGS=-std=c99 -g

all: base opt

base: TestBase.o MeasureFunction.o
		$(CC) -o base TestBase.o MeasureFunction.o

opt: TestFast.o MeasureFunction.o
		$(CC) -o opt TestFast.o MeasureFunction.o

.PHONY: clean

clean:
		rm *.o
