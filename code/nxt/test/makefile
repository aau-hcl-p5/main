IDIR =../inc
CC=gcc
CFLAGS=-I$(IDIR) -I./ -fPIC -fprofile-arcs -ftest-coverage -g -lm -DTEST

LIBS=-lm

SRCTEST = $(wildcard ./*.c)

SRCC = $(wildcard ../src/*.c)
CSRC = $(filter-out ../src/nxt.c ../src/data_receive.c ../src/movement.c ../src/init_screen.c ../src/display_data.c, $(SRCC))
COVSRC = $(CSRC:.c=.gcno)
COV = $(COVSRC:../src/%=%)

SRC = $(SRCTEST) $(CSRC)

testsuite: $(SRC)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean test coverage
test: testsuite
	./testsuite

coverage: testsuite
	gcov $(COV)  && grep "#####\|Source:" . -rh | sed -e "s/ -:    0:Source://g"

clean:
	rm -rf testsuite *.gcno *.gcda *.gcov
