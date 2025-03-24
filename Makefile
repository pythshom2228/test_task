CC=g++
CFLAGS=-Wall -Wextra -std=c++17 -O2

TARGET=program
SOURCES=program.cpp
OBJECTS=program.o
SHARED=log

OUT_DIR=build

.PHONY: all clear

all: ${OUT_DIR} ${TARGET} test


${TARGET}: ${OBJECTS} ${SHARED} main.o
	${CC} ${CFLAGS} ${OBJECTS} main.o -L${OUT_DIR} -l${SHARED} -pthread -Wl,-rpath=. -o ${OUT_DIR}/${TARGET}

${SHARED}: log.o
	${CC} -shared log.o -o ${OUT_DIR}/lib${SHARED}.so

test: test.o program.o
	${CC} ${CFLAGS} test.o -L${OUT_DIR} -l${SHARED} program.o -Wl,-rpath=. -o ${OUT_DIR}/test

${OUT_DIR}:
	mkdir ${OUT_DIR}

${OBJECTS}: ${SOURCES}
	${CC} ${CFLAGS} -c ${SOURCES}


main.o: main.cpp
	${CC} ${CFLAGS} -c main.cpp

test.o: test.cpp
	${CC} ${CFLAGS} -c test.cpp


log.o: log.cpp
	${CC} ${CFLAGS} -fPIC -c log.cpp

clean: 
	rm -rf *.o
