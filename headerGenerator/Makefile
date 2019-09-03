CC = g++ -I.
CFLAGS = -c -pedantic -ansi -Wall -g


headerGenerator: headerGenerator.o test.o
	$(CC) -o headerGenerator headerGenerator.o test.o

#-lDS -L./mostUpdatedDS/DS/
	
test.o: test.cpp headerGenerator.h
		$(CC) $(CFLAGS) test.cpp


headerGenerator.o: headerGenerator.cpp headerGenerator.h
	$(CC) $(CFLAGS) headerGenerator.cpp
	

#timeOps.o: ../time/timeOps.cpp ../time/timeOps.h
	#$(CC) $(CFLAGS) ../time/timeOps.cpp
	
	
clean:
	rm -rf test.o
	rm -rf headerGenerator.o
	rm -f headerGenerator
	
