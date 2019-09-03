CC = g++ -I. -I../mutex -I../time -I../ -pthread
CFLAGS = -c -pedantic -ansi -Wall -g

all: make condVar

condVar: condVar.o test.o ../mutex/mutex.o ../mutex/timeOps.o
	$(CC) -o condVar condVar.o test.o ../mutex/mutex.o ../mutex/timeOps.o

#-lDS -L./mostUpdatedDS/DS/
	
test.o: test.cpp condVar.h
		$(CC) $(CFLAGS) test.cpp


condVar.o: condVar.cpp condVar.h ../uncopyable/uncopyable.h ../mutex/mutex.h ../exceptionTemplate.h
	$(CC) $(CFLAGS) condVar.cpp
	


make:
	cd ../mutex/ && make
	
clean:
	cd ../mutex/ && make clean

	rm -rf test.o
	rm -rf condVar.o
	rm -f condVar
	
