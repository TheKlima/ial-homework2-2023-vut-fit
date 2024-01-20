CC=gcc
CFLAGS=-Wall -std=c11 -pedantic -lm -DEXA
FILES=btree.c ../btree.c ../test_util.c ../test.c ../exa/exa.c

.PHONY: test clean

test: $(FILES)
	$(CC) $(CFLAGS) -o $@ $(FILES)

clean:
	rm -f test
