
all:
	$(error Error: use 'make proc' or 'make thread')
multitest_proc:
	gcc -c multitest_proc.c

multitest_thread:
	gcc -c multitest_thread.c

proc: multitest_proc.o searchtest.c
	gcc -Wall -g -o searchtest searchtest.c multitest_proc.o

thread: multitest_thread.o searchtest.c
	gcc -Wall -g -o searchtest searchtest.c multitest_thread.o
clean:
	rm -f *.o multitest_proc