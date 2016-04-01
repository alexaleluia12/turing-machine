CC=g++
FLAGS=-std=c++11 -Wall
DIR=turingmachine/
BIN=bin/

main: jsoncpp.o machine.o main.o
	${CC} ${FLAGS} ${BIN}jsoncpp.o ${BIN}machine.o ${BIN}main.o -o ${BIN}main

jsoncpp.o: ${DIR}jsoncpp.cpp ${DIR}json/json.h
	${CC} ${FLAGS} -c ${DIR}jsoncpp.cpp -o ${BIN}jsoncpp.o

machine.o: ${DIR}machine.cpp ${DIR}machine.h jsoncpp.o
	${CC} ${FLAGS} -c ${DIR}machine.cpp -o ${BIN}machine.o

main.o: ${DIR}machine.h ${DIR}json/json.h ${DIR}main.cpp
	${CC} ${FLAGS} -c ${DIR}main.cpp -o ${BIN}main.o

clear:
	rm bin/*



