CC = g++
CFLAGS = -g -Wall
LIBS = -lSDL2 -lSDL2_ttf
SOURCES = $(wildcard *.cpp)
OBJECT = $(SOURCES:.cpp=.o)
EXE = flap

$(EXE): $(OBJECT) 
	$(CC) $(CFLAGS) $(OBJECT) $(LIBS) -o $(EXE)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@
