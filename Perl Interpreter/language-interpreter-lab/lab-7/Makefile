
# The top level rule indicates how to link everything together into calc

calc: main.o symbol_map.o expr.o scanner.o parser.o
	gcc main.o symbol_map.o expr.o scanner.o parser.o -o interpreter.out -lm

# This pattern indicates that any .o file depends
# upon the .c file of the same name, and all of the .h files.
# So, if a .o file is needed, it is built automatically.

%.o: %.c *.h
	gcc -Wall -c $< -o $@

# Only the files generated by flex and bison need explicit rules.

scanner.c: scanner.flex parser.h
	flex -oscanner.c scanner.flex

parser.c parser.h: parser.bison
	bison --defines=parser.h --output=parser.c -v parser.bison

# clean causes all intermediate files to be deleted.

clean:
	rm -f parser.c parser.output parser.h scanner.c *.o interpreter.out

