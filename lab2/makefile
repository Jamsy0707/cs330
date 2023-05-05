#James Sieben 200455325

#define some variables
cc = gcc

# leads comments in a line 
# Build all: default target

all : demo

# Separate compilation to build object files
main.o : main.c functions.h 
	$(cc) -c -ggdb main.c

functions.o : functions.c functions.h 
	$(cc) -c -ggdb functions.c

# linking
#demo is a target which depends upon main.o and functions.o 
#"$(cc) main.o functions.o -o demo" is the command to produce the executable file
#You need to use a TAB before $(cc) 
demo : main.o functions.o
	$(cc) main.o functions.o -o demo

# Testing
check : all
	./demo

# Clean up all build targets so that one may get a clean build
clean :
	rm -f *.o
squeaky : clean
	rm -f demo
	rm core*.[0-9]*
# Valgrind 
valgrind : all
	valgrind --leak-check=yes ./demo