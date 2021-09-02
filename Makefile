exec:
	-gcc src/*.c -o asm

run-ex-1:
	-./asc ./examples/ex-1.asc --assembly

run-ex-2:
	-./asc ./examples/ex-2.asc --assembly

run-ex-3:
	-./asc ./examples/ex-3.asc --assembly

run-ex-4:
	-./asc ./examples/ex-4.asc --assembly