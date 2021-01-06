#spec source files
SRC = testSqrt.c fastInverseSqrt.c
#spec targ file
TARG = testSqrt
#spec compiler, flags and libs
CC = gcc
OPTS = -Wall -Werror -lm

#compile
all:
	$(CC) -o $(TARG) $(SRC) $(OPTS)

#clean
clean:
	$(RM) $(TARG)
