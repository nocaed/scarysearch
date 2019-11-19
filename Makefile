
all:
	$(error Error: use 'make proc' or 'make thread')
multitest_proc:
	gcc -c -lm multitest_proc.c

multitest_thread:
	gcc -c-lm multitest_thread.c

proc: multitest_proc.o searchtest.c
	gcc -Wall -lm -g -o searchtest searchtest.c multitest_proc.o

thread: multitest_thread.o searchtest.c
	gcc -Wall -lm -g -pthread -o searchtest searchtest.c multitest_thread.o
clean:
	rm -f *.o