CC = g++ -I. -I../htmlPageGenerator -I../headerGenerator -I../tokenizer -I../argumentsTranslator
CFLAGS = -c -pedantic -ansi -Wall -g

all: make httpRequest

httpRequest: httpRequest.o test.o ../htmlPageGenerator/htmlPageGenerator.o ../headerGenerator/headerGenerator.o ../tokenizer/tokenizer.o
	$(CC) -o httpRequest httpRequest.o test.o ../htmlPageGenerator/htmlPageGenerator.o ../headerGenerator/headerGenerator.o ../tokenizer/tokenizer.o

#-lDS -L./mostUpdatedDS/DS/
	
test.o: test.cpp httpRequest.h
		$(CC) $(CFLAGS) test.cpp


httpRequest.o: httpRequest.cpp httpRequest.h ../htmlPageGenerator/htmlPageGenerator.h ../headerGenerator/headerGenerator.h ../argumentsTranslator/argumentsTranslator.h
	$(CC) $(CFLAGS) httpRequest.cpp
	

#timeOps.o: ../time/timeOps.cpp ../time/timeOps.h
	#$(CC) $(CFLAGS) ../time/timeOps.cpp
	

make:
	cd ../htmlPageGenerator/ && make
	cd ../headerGenerator/ && make
	

clean:
	cd ../htmlPageGenerator/ && make clean
	cd ../headerGenerator/ && make clean
	
	rm -rf test.o
	rm -rf httpRequest.o
	rm -f httpRequest
	
