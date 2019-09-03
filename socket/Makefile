CC = g++ -I.
CFLAGS = -c -pedantic -ansi -Wall -g


socket: socket.o test.o
	$(CC) -o socket socket.o test.o

#-lDS -L./mostUpdatedDS/DS/
	
test.o: test.cpp socket.h
		$(CC) $(CFLAGS) test.cpp


socket.o: socket.cpp socket.h
	$(CC) $(CFLAGS) socket.cpp
	

#timeOps.o: ../time/timeOps.cpp ../time/timeOps.h
	#$(CC) $(CFLAGS) ../time/timeOps.cpp
	
	
clean:
	rm -rf test.o
	rm -rf socket.o
	rm -f socket
	
