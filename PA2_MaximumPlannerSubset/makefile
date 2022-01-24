# CC and CFLAGS are varilables
CC = g++
CFLAGS = -c
AR = ar
ARFLAGS = rcv
# -c option ask g++ to compile the source files, but do not link.
# -g option is for debugging version
# -O2 option is for optimized version
DBGFLAGS = -g -D_DEBUG_ON_
OPTFLAGS = -O2

all	: bin/mps
	@echo -n ""

# optimized version
bin/mps	: function_opt.o main_opt.o
			$(CC) $(OPTFLAGS) function_opt.o main_opt.o -o bin/mps
main_opt.o 	   	: src/main.cpp src/function.h
			$(CC) $(CFLAGS) $< -o $@
function_opt.o	: src/function.cpp src/function.h
			$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@



# clean all the .o and executable files
clean:
		rm -rf *.o bin/*

