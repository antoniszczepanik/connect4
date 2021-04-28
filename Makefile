CC=em++
C_FLAGS=-Wall -s WASM=1 -s EXPORT_ALL=1 -s ERROR_ON_UNDEFINED_SYMBOLS=0
L_FLAGS=--bind
TARGET=out/wasm.js
FILES=objects/board.o objects/search.o objects/main.o
CLIENT_FILES=client/index.html client/style.css client/script.js

${TARGET}: ${FILES} client
		${CC} -o ${TARGET} ${FILES} ${L_FLAGS}

objects/main.o: main.cpp board.h ${CLIENT_FILES}
		${CC} -o objects/main.o -c main.cpp ${C_FLAGS}
		cp ${CLIENT_FILES} out/

objects/board.o: board.cpp board.h search.h
		${CC} -o objects/board.o -c board.cpp ${C_FLAGS}

objects/search.o: search.cpp search.h board.h
		${CC} -o objects/search.o -c search.cpp ${C_FLAGS}

.PHONY: clean

clean:
	-rm -f ${FILES} ${TARGET} out/*
