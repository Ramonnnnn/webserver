CC = g++ -I. -I../mutex -I../semaphore -I../time -pthread
CFLAGS = -c -pedantic -ansi -Wall -g

all: make thread

thread: thread.o test.o ../mutex/mutex.o ../semaphore/semaph.o ../mutex/timeOps.o
	$(CC) -o thread thread.o test.o ../mutex/mutex.o ../semaphore/semaph.o ../mutex/timeOps.o

#-lDS -L./mostUpdatedDS/DS/
	
test.o: test.cpp thread.h
		$(CC) $(CFLAGS) test.cpp


thread.o: thread.cpp thread.h uncopyable.h irunnable.h threadExcept.h ../mutex/mutex.h ../semaphore/semaph.h guardAdv.h
	$(CC) $(CFLAGS) thread.cpp
	


make:
	cd ../mutex/ && make
	cd ../semaphore/ && make
	

clean:
	cd ../mutex/ && make clean
	cd ../semaphore/ && make clean
	
	rm -rf test.o
	rm -rf thread.o
	rm -f thread
	
