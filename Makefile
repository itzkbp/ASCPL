exec    = ./bin/a.out
sources = $(wildcard src/*.c)
objects = $(sources:.c=.o)
flags   = -g -Wall -lm -ldl -fPIC -rdynamic

$(exec) : $(objects)
	gcc $(objects) $(flags) -o $(exec)

%.o: %.c include/%.h
	gcc -c $(flags) $< -o $@

run:
	-./bin/a.out ./examples/ex-1.asc

clean:
	-rm src/*.o
	-rm ./bin/*.out
	-clear