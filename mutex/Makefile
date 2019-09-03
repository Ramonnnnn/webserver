CC = g++ -I. -I../time/  -pthread
CFLAGS = -c -pedantic -ansi -Wall -g


mutex: mutex.o test.o timeOps.o
	$(CC) -o mutex mutex.o test.o timeOps.o

#-lDS -L./mostUpdatedDS/DS/
	
test.o: test.cpp mutex.h
		$(CC) $(CFLAGS) test.cpp


mutex.o: mutex.cpp mutex.h uncopyable.h mutexExcept.h
	$(CC) $(CFLAGS) mutex.cpp
	

timeOps.o: ../time/timeOps.cpp ../time/timeOps.h
	$(CC) $(CFLAGS) ../time/timeOps.cpp
	
	
clean:
	rm -rf test.o
	rm -rf mutex.o
	rm -f mutex
	
