CC=g++
CFLAGS=-O3
LFLAGS=-lsfml-graphics -lsfml-window -lsfml-system 
AR=ar
SRCS=highrisedev.cpp physics.cpp camera.cpp image.cpp animation.cpp \
     floorbase.cpp office.cpp level.cpp tiler.cpp lobby.cpp elevator.cpp \
     elevatorBase.cpp elevatorMachine.cpp elevatorPit.cpp elevatorShaft.cpp \
     highRiseException.cpp routes.cpp
OBJS=highrisedev.o physics.o camera.o image.o animation.o \
     floorbase.o office.o level.o tiler.o lobby.o elevator.o \
     elevatorBase.o elevatorMachine.o elevatorPit.o elevatorShaft.o \
     highRiseException.o routes.o

all : highrisedev

highrisedev : $(OBJS) $(SRCS)
	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) -o $@

.c.o : $(SRCS)
	$(CC) -c $(CFLAGS) $*.c

clean : 
	rm -rf *.o *.a *.exe stdout.txt stderr.txt
    
