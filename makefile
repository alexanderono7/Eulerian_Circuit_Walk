EXEC = run
CC = g++
CFLAGS = -c -g -Wall

$(EXEC) :clean main.o graph.o move
	$(CC) -o $(EXEC) ./bin/*.o
	
main.o	:main.cpp
	$(CC) $(CFLAGS) main.cpp
graph.o	:graph.h graph.cpp
	$(CC) $(CFLAGS) graph.cpp
move: 
	-mv *.o ./bin
clean:
	-rm ./bin/*.o
