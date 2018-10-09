IDIR =../inc
CC=gcc
CFLAGS=-I$(IDIR)

LIBS=-lm

CSRC = $(wildcard ./*.c) \
       $(wildcard ../src/*.c)

TMPVAR := $(CSRC)
CSRC = $(filter-out ../src/nxt.c, $(TMPVAR))

testsuite: $(CSRC)
	$(CC) -o $@ $^ -DTEST -I./ $(CFLAGS) $(LIBS)

.PHONY: clean test
test: testsuite
	./testsuite

clean:
	rm -f testsuite