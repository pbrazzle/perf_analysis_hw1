CC=gcc
CFLAGS=-std=c99

all: base opt

base: TopologicalSortAI.o
        $(CC) -o base TopologicalSortAI.o

opt: TopologicalSortAIFast.o
        $(CC) -o opt TopologicalSortAIFast.o

.PHONY: clean

clean:
        rm *.o
