CC = g++ -I.
CFLAGS = -c -pedantic -ansi -Wall -g


output: output.o test.o
	$(CC) -o output output.o test.o

#-lDS -L./mostUpdatedDS/DS/
	
test.o: test.cpp output.h
		$(CC) $(CFLAGS) test.cpp


output.o: output.cpp output.h
	$(CC) $(CFLAGS) output.cpp
	

#timeOps.o: ../time/timeOps.cpp ../time/timeOps.h
	#$(CC) $(CFLAGS) ../time/timeOps.cpp
	
	
clean:
	rm -rf test.o
	rm -rf output.o
	rm -f output
	
