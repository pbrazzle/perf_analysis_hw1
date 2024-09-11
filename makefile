CC=gcc
CFLAGS=-std=c11 -g -O0

all: base opt

base: TestBase.o MeasureFunction.o
		$(CC) -o base TestBase.o MeasureFunction.o -lrt

opt: TestFast.o MeasureFunction.o
		$(CC) -o opt TestFast.o MeasureFunction.o -lrt

.PHONY: clean

clean:
		rm *.o
