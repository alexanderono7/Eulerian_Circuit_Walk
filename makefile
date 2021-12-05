EXEC = run
CC = g++
CFLAGS = -c -g -Wall
# $(EXEC) has the value of shell variable EXEC, which is run.
# run depends on the files main.o graph.o heap.o
$(EXEC) :main.o graph.o
# run is created by the command g++ -o run main.o graph.o
# note that the TAB before $(CC) is REQUIRED...
	$(CC) -o $(EXEC) main.o graph.o
# main.o depends on the files main.h main.cpp
main.o	:main.cpp
# main.o is created by the command g++ -c -Wall main.cpp
# note that the TAB before $(CC) is REQUIRED...
	$(CC) $(CFLAGS) main.cpp
graph.o	:graph.h graph.cpp
	$(CC) $(CFLAGS) graph.cpp
clean   :
	rm *.o
