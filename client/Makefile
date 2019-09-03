CC = g++ -I. -I../webServer
CFLAGS = -c -pedantic -ansi -Wall -g


webClient: webClient.o test.o
	$(CC) -o webClient webClient.o test.o

#-lDS -L./mostUpdatedDS/DS/
	
test.o: test.cpp webClient.h
		$(CC) $(CFLAGS) test.cpp


webClient.o: webClient.cpp webClient.h
	$(CC) $(CFLAGS) webClient.cpp
	

#timeOps.o: ../time/timeOps.cpp ../time/timeOps.h
	#$(CC) $(CFLAGS) ../time/timeOps.cpp
	
	
clean:
	
	rm -rf webClient.o
	rm -f webClient
	
