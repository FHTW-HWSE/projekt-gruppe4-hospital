CC=gcc
CFLAGS=-Iinclude
DEPS=include/functions.h
EXEC=bin/myHospital

all: $(EXEC)

$(EXEC): build/main.o build/functions.o
	$(CC) -o $(EXEC) build/main.o build/functions.o $(CFLAGS)

build/main.o: src/main.c $(DEPS)
	$(CC) -c src/main.c -o build/main.o $(CFLAGS)

build/functions.o: src/functions.c $(DEPS)
	$(CC) -c src/functions.c -o build/functions.o $(CFLAGS)

.PHONY: clean

clean:
	rm -f build/*.o $(EXEC)
