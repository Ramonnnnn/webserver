CC = g++ -I. -I../tokenizer -I../argumentsTranslator
CFLAGS = -c -pedantic -ansi -Wall -g

all: make htmlPageGenerator

htmlPageGenerator: htmlPageGenerator.o test.o ../tokenizer/tokenizer.o
	$(CC) -o htmlPageGenerator htmlPageGenerator.o test.o ../tokenizer/tokenizer.o

#-lDS -L./mostUpdatedDS/DS/
	
test.o: test.cpp htmlPageGenerator.h
		$(CC) $(CFLAGS) test.cpp


htmlPageGenerator.o: htmlPageGenerator.cpp htmlPageGenerator.h ../tokenizer/tokenizer.h ../argumentsTranslator/argumentsTranslator.h
	$(CC) $(CFLAGS) htmlPageGenerator.cpp
	

#timeOps.o: ../time/timeOps.cpp ../time/timeOps.h
	#$(CC) $(CFLAGS) ../time/timeOps.cpp
	

make:
	cd ../tokenizer/ && make

clean:
	cd ../tokenizer/ && make clean
	
	rm -rf test.o
	rm -rf htmlPageGenerator.o
	rm -f htmlPageGenerator
	
