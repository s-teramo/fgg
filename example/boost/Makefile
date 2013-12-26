CC = g++
GLUTIN = 
CFLAGS = -O2 -Wall -I../..
LD = g++
LFLAGS = -O2 -L../..
LIBS = -lfgg -lm

.SUFFIXES:
.SUFFIXES: .o .cpp

PROGS = dijkstra johnson
OBJS = $(PROGS:=.o)

all: $(PROGS)

.cpp.o:
	$(CC) $(CFLAGS) -c $<
.o:
	$(LD) $(LFLAGS) $*.o -o $* $(LIBS)
.cpp:
	$(CC) $(CFLAGS) -c $<
	$(LD) $(LFLAGS) $(LIBS) $*.o -o $*
clean:
	rm $(PROGS) $(OBJS)
