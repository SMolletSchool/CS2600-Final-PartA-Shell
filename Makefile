CC=gcc

ifeq ($(OS),Windows_NT)
	DELETE=del
else
	DELETE=rm -f
endif


all: buildShell

buildShell:
	$(CC) -o lsh src/(s)hell.c

buildLibraryImp:
	$(CC) -DLSH_USE_STD_GETLINE -o lsh src/main.c

clean:
	$(DELETE) *.o