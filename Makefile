exec    = ./bin/asc.out
sources = $(wildcard src/*.c)
objects = $(sources:.c=.o)
flags   = -g -Wall -lm -ldl -fPIC -rdynamic

$(exec) : $(objects)
	gcc $(objects) $(flags) -o $(exec)

%.o: %.c include/%.h
	gcc -c $(flags) $< -o $@

run:
	-$(exec) ./examples/ex-1.asc

clean:
	-rm src/*.o
	-rm ./bin/*
	-clear

asc:
	-as --32 ./bin/out.s -o ./bin/out.o
	-ld ./bin/out.o -o ./bin/test -m elf_i386
	-./bin/test
	-echo $$?