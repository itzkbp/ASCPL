COMPILER  = gcc
TOCOMPILE = *.c
OUTFILE   = asc
ARGUMENT = ./examples/ex-4.asc

all: compile run

compile:
	@echo "Compiling file(s)..."
	${COMPILER} ${TOCOMPILE} -o ${OUTFILE}
	@echo "Compiling Finished...\n"

run:
	@echo "Running file (${OUTFILE})"
	./${OUTFILE} ${ARGUMENT}
	@echo "\nCompleted!!!"

clean:
	@echo "Clearing output files..."
	rm ${OUTFILE}
