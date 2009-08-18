CC=g++
CFLAGS=-O3
LFLAGS=-lsfml-graphics -lsfml-window -lsfml-system 
AR=ar
SRCS=tower.cpp physics.cpp camera.cpp image.cpp animation.cpp
OBJS=tower.o physics.o camera.o image.o animation.o

all : tower

tower : $(OBJS) $(SRCS)
	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) -o $@

.c.o : $(SRCS)
	$(CC) -c $(CFLAGS) $*.c

clean : 
	rm -rf *.o *.a *.exe stdout.txt stderr.txt
    
