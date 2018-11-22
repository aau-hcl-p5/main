IDIR =../inc
CC=gcc
CFLAGS=-I$(IDIR) -I./ -fPIC -fprofile-arcs -ftest-coverage -g -lm -DTEST

LIBS=-lm

SRCTEST = $(wildcard ./*.c)

SRCC = $(wildcard ../src/*.c)
#CSRC = $(filter-out ../src/nxt.c, $(SRCC))
COVSRC = $(SRCC:.c=.gcno)
COV = $(COVSRC:../src/%=%)

SRC = $(SRCTEST) $(SRCC)

testsuite: $(SRC)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean test coverage
test: testsuite
	./testsuite

coverage: testsuite
	gcov $(COV)  && grep "#####\|Source:" . -rh | sed -e "s/ -:    0:Source://g"

clean:
	rm -rf testsuite *.gcno *.gcda *.gcov
