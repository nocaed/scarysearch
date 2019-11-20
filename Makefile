
all:
	$(error Error: use 'make proc' or 'make thread')
multitest_proc:
	gcc -c -lm -g -pthread multitest_proc.c

multitest_thread:
	gcc -c-lm -g -fstanitize-recover=all multitest_thread.c

proc: multitest_proc.o searchtest.c
	gcc -Wall -lm -g -o searchtest searchtest.c multitest_proc.o

thread: multitest_thread.o searchtest.c
	gcc -pthread -o searchtest searchtest.c multitest_thread.o
clean:
	rm -f *.o