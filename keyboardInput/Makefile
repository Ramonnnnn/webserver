CC = g++ -I.
CFLAGS = -c -pedantic -ansi -Wall -g


keyboardInput: keyboardInput.o test.o
	$(CC) -o keyboardInput keyboardInput.o test.o

#-lDS -L./mostUpdatedDS/DS/
	
test.o: test.cpp keyboardInput.h
		$(CC) $(CFLAGS) test.cpp


keyboardInput.o: keyboardInput.cpp keyboardInput.h
	$(CC) $(CFLAGS) keyboardInput.cpp
	

#timeOps.o: ../time/timeOps.cpp ../time/timeOps.h
	#$(CC) $(CFLAGS) ../time/timeOps.cpp
	
	
clean:
	
	rm -rf keyboardInput.o
	rm -f keyboardInput
	
