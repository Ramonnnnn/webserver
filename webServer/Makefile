CC = g++ -I. -I../output -I../socketOutput -I../listeningSocket -I../socket -I../httpRequest -I../htmlPageGenerator -I../thread -I../mutex -I../semaphore -I../time -I../headerGenerator -I../safeQ -I../threadPool -I../uncopyable -I../condVar -I../tokenizer -I../ -I../argumentsTranslator -pthread
CFLAGS = -c -pedantic -ansi -Wall -g

all: make webServer

webServer: webServer.o test.o ../socketOutput/socketOutput.o ../listeningSocket/listeningSocket.o ../socket/socket.o ../httpRequest/httpRequest.o ../htmlPageGenerator/htmlPageGenerator.o ../thread/thread.o ../mutex/mutex.o ../semaphore/semaph.o ../mutex/timeOps.o ../headerGenerator/headerGenerator.o ../threadPool/threadPool.o ../condVar/condVar.o ../tokenizer/tokenizer.o
	$(CC) -o webServer webServer.o test.o ../socketOutput/socketOutput.o ../listeningSocket/listeningSocket.o ../socket/socket.o ../httpRequest/httpRequest.o ../htmlPageGenerator/htmlPageGenerator.o ../thread/thread.o ../mutex/mutex.o ../semaphore/semaph.o ../mutex/timeOps.o ../headerGenerator/headerGenerator.o ../threadPool/threadPool.o ../condVar/condVar.o ../tokenizer/tokenizer.o

#-lDS -L./mostUpdatedDS/DS/
	
test.o: test.cpp webServer.h
		$(CC) $(CFLAGS) test.cpp


webServer.o: webServer.cpp webServer.h ../output/output.h ../socketOutput/socketOutput.h ../listeningSocket/listeningSocket.h ../httpRequest/httpRequest.h ../threadPool/threadPool.h
	$(CC) $(CFLAGS) webServer.cpp
	

#timeOps.o: ../time/timeOps.cpp ../time/timeOps.h
	#$(CC) $(CFLAGS) ../time/timeOps.cpp
	
	
make:
	cd ../listeningSocket/ && make
	cd ../httpRequest/ && make
	cd ../socketOutput/ && make
	cd ../threadPool/ && make
	

clean:
	cd ../listeningSocket/ && make clean
	cd ../httpRequest/ && make clean
	cd ../socketOutput/ && make clean
	cd ../threadPool/ && make clean
	
	rm -rf test.o
	rm -rf webServer.o
	rm -f webServer
	
