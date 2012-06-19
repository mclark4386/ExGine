PROG="../exo"
LEPROG="../levelEditor"

ifeq ($(shell uname),Darwin)
	CC=clang++
else
	CC=g++
endif

ifeq ($(shell uname),Darwin)
	CFLAGS=-Wall -std=c++0x
else
	CFLAGS=-Wall -fopenmp -std=c++0x
endif

DEBUG=-ggdb3

ifeq ($(shell uname),Darwin)
	LIBS=-framework OpenGL -framework GLUT -framework Cocoa -DMACMAN -stdlib=libc++
else
	LIBS=-lGL -lglut -lGLU -lopenal -lalut -logg -lvorbis -lvorbisfile
endif

LESRC= levelEditor.cpp
GSRC= Exo.cpp

release:
	$(CC) $(CFLAGS) $(LESRC) $(LIBS) -o $(LEPROG) 

debug:
	$(CC) $(CFLAGS) $(DEBUG) $(LESRC) $(LIBS) -o $(LEPROG)

exorelease:
	$(CC) $(CFLAGS) $(GSRC) $(LIBS) -o $(PROG) 
	
exodebug:
	$(CC) $(CFLAGS) $(DEBUG) $(GSRC) $(LIBS) -o $(PROG) 

default:
	$(CC) $(CFLAGS) $(LESRC) $(LIBS) -o $(LEPROG) 
	
32bit:
	$(CC) $(CFLAGS) -m32 $(GSRC) $(LIBS) -o $(PROG).32.bin 
