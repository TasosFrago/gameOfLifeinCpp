#COMPILER
CC = g++

TARGET = src/main.cpp
INCLUDES = src/RenderWindow.cpp
EXEC = bin/helloSdl

#COMPILER FLAGS
#sup = -w
LINKER = -lSDL2

FLAGS = $(sup) $(LINKER)

all : $(TARGET) $(INCLUDES)
	$(CC) $(TARGET) $(INCLUDES) $(FLAGS) -o $(EXEC)

exec:
	./$(EXEC)

clean:
	rm $(EXEC) *.o
