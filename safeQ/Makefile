CC = g++ -I.. -I../mutex -I../condVar -I../semaphore -I../time -pthread
CFLAGS = -c -pedantic -ansi -Wall -g

all: make safeQ

safeQ: safeQ.o test.o ../mutex/mutex.o ../semaphore/semaph.o ../mutex/timeOps.o ../condVar/condVar.o
	$(CC) -o safeQ safeQ.o test.o ../mutex/mutex.o ../semaphore/semaph.o ../mutex/timeOps.o ../condVar/condVar.o

#-lDS -L./mostUpdatedDS/DS/
	
test.o: test.cpp safeQ.h
		$(CC) $(CFLAGS) test.cpp


safeQ.o: safeQ.cpp safeQ.h ../mutex/mutex.h ../semaphore/semaph.h ../condVar/condVar.h
	$(CC) $(CFLAGS) safeQ.cpp
	


make:
	cd ../condVar/ && make
	cd ../semaphore/ && make
	

clean:
	cd ../condVar/ && make clean
	cd ../semaphore/ && make clean
	
	rm -rf test.o
	rm -rf safeQ.o
	rm -f safeQ
	
