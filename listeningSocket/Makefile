CC = g++ -I. -I../socket
CFLAGS = -c -pedantic -ansi -Wall -g

all: make listeningSocket

listeningSocket: listeningSocket.o test.o ../socket/socket.o
	$(CC) -o listeningSocket listeningSocket.o test.o ../socket/socket.o

#-lDS -L./mostUpdatedDS/DS/
	
test.o: test.cpp listeningSocket.h
		$(CC) $(CFLAGS) test.cpp


listeningSocket.o: listeningSocket.cpp listeningSocket.h ../socket/socket.h
	$(CC) $(CFLAGS) listeningSocket.cpp
	

#timeOps.o: ../time/timeOps.cpp ../time/timeOps.h
	#$(CC) $(CFLAGS) ../time/timeOps.cpp
	

make:
	cd ../socket/ && make
	

clean:
	cd ../socket/ && make clean
	
	rm -rf test.o
	rm -rf listeningSocket.o
	rm -f listeningSocket
	
