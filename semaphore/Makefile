CC = g++ -I. -pthread
CFLAGS = -c -pedantic -ansi -Wall -g


semaph: semaph.o test.o
	$(CC) -o semaph semaph.o test.o

#-lDS -L./mostUpdatedDS/DS/
	
test.o: test.cpp semaph.h
		$(CC) $(CFLAGS) test.cpp


semaph.o: semaph.cpp semaph.h uncopyable.h semaphExcept.h
	$(CC) $(CFLAGS) semaph.cpp
	

	
	
clean:
	rm -rf test.o
	rm -rf semaph.o
	rm -f semaph
	
