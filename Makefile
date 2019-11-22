
all:
	$(error Error: use 'make proc' or 'make thread')
multitest_proc:
	gcc -c multitest_proc.c

multitest_thread:
	gcc -c- mythread.c

proc: multitest_proc.o searchtest.c
	gcc -Wall -o searchtest searchtest.c multitest_proc.o -lm

thread: multitest_thread.o searchtest.c
	gcc -pthread -o searchtest searchtest.c multitest_thread.o -lm
clean:
	rm -f *.o