CC = g++ -I. -I../uncopyable -I../safeQ -I../thread -I../mutex -I../semaphore -I../time -I../condVar -I../ -pthread
CFLAGS = -c -pedantic -ansi -Wall -g

all: make threadPool

threadPool: threadPool.o test.o ../thread/thread.o ../mutex/mutex.o ../semaphore/semaph.o ../mutex/timeOps.o ../condVar/condVar.o
	$(CC) -o threadPool threadPool.o test.o ../thread/thread.o ../mutex/mutex.o ../semaphore/semaph.o ../mutex/timeOps.o ../condVar/condVar.o

#-lDS -L./mostUpdatedDS/DS/
	
test.o: test.cpp threadPool.h
		$(CC) $(CFLAGS) test.cpp


threadPool.o: threadPool.cpp threadPool.h ../uncopyable/uncopyable.h ../safeQ/safeQ.h ../thread/thread.h
	$(CC) $(CFLAGS) threadPool.cpp
	

#timeOps.o: ../time/timeOps.cpp ../time/timeOps.h
	#$(CC) $(CFLAGS) ../time/timeOps.cpp


make:
	cd ../thread/ && make
	cd ../safeQ/ && make

clean:
	cd ../thread/ && make clean
	cd ../safeQ/ && make
	
	rm -rf test.o
	rm -rf threadPool.o
	rm -f threadPool
	
