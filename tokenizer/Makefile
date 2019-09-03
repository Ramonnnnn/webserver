CC = g++ -I.
CFLAGS = -c -pedantic -ansi -Wall -Werror -g

#-std=c++11


tokenizer: testTokenizer.o tokenizer.o
	$(CC) -o tokenizer testTokenizer.o tokenizer.o

#-lDS -L./mostUpdatedDS/DS/
	
	
testTokenizer.o: testTokenizer.cpp tokenizer.h
	$(CC) $(CFLAGS) testTokenizer.cpp
	
tokenizer.o: tokenizer.cpp tokenizer.h
	$(CC) $(CFLAGS) tokenizer.cpp
	

	
	
clean:
	rm -rf testTokenizer.o
	rm -rf tokenizer.o
	rm -f tokenizer
	
