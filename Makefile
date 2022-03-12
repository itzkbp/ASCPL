COMPILER  = gcc
TOCOMPILE = *.c
OUTFILE   = asc

all: compile run

compile:
	@echo "Compiling file(s)..."
	${COMPILER} ${TOCOMPILE} -o ${OUTFILE}
	@echo "Compiling Finished...\n"

run:
	@echo "Running file (${OUTFILE})"
	./${OUTFILE}
	@echo "\nCompleted!!!"

clean:
	@echo "Clearing output files..."
	rm ${OUTFILE}
