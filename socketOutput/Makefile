CC = g++ -I. -I../output -I../socket
CFLAGS = -c -pedantic -ansi -Wall -g


socketOutput: socketOutput.o test.o ../socket/socket.o
	$(CC) -o socketOutput socketOutput.o test.o ../socket/socket.o

#-lDS -L./mostUpdatedDS/DS/
	
test.o: test.cpp socketOutput.h
		$(CC) $(CFLAGS) test.cpp


socketOutput.o: socketOutput.cpp socketOutput.h ../output/output.h ../socket/socket.h
	$(CC) $(CFLAGS) socketOutput.cpp
	

#timeOps.o: ../time/timeOps.cpp ../time/timeOps.h
	#$(CC) $(CFLAGS) ../time/timeOps.cpp
	
	
clean:
	
	rm -rf test.o
	rm -rf socketOutput.o
	rm -f socketOutput
	
