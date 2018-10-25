IDIR =../inc
CC=gcc
CFLAGS=-I$(IDIR) -I./ -fPIC -fprofile-arcs -ftest-coverage -g -lm -DTEST

LIBS=-lm

CSRC = $(wildcard ./*.c) \
       $(wildcard ../src/*.c)

TMPVAR := $(CSRC)
CSRC = $(filter-out ../src/nxt.c ../src/data_receive.c ../src/movement.c ../src/init_screen.c ../src/display_data.c, $(TMPVAR))

testsuite: $(CSRC)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean test
test: testsuite
	./testsuite

clean:
	rm -f testsuite *.gcno
