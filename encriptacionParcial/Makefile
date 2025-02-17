CC = g++
CFLAGS = -Wall -Wextra -std=c++17

all: fileencrypt

fileencrypt: main.o FileEncryption.o
	$(CC) $(CFLAGS) -o fileencrypt main.o FileEncryption.o

main.o: main.cpp FileEncryption.h
	$(CC) $(CFLAGS) -c main.cpp

FileEncryption.o: FileEncryption.cpp FileEncryption.h
	$(CC) $(CFLAGS) -c FileEncryption.cpp

clean:
	rm -f fileencrypt *.o