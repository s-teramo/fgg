CC = g++
IGRAPH_INCLUDE_PATH = /opt/local/include
CFLAGS = -O2 -Wall -I.. -I$(IGRAPH_INCLUDE_PATH) 
LD = g++
IGRAPH_LIBRARY_PATH = /opt/local/lib
LFLAGS = -O2 -L.. -L$(IGRAPH_LIBRARY_PATH)
LIBS = -lfgg -ligraph

.SUFFIXES:
.SUFFIXES: .o .c

PROGS = comp_diam dump_gml
OBJS = $(PROGS:=.o)

all: $(PROGS)

.c.o:
	$(CC) $(CFLAGS) -c $<
.o:
	$(LD) $(LFLAGS) $*.o -o $* $(LIBS)
.c:
	$(CC) $(CFLAGS) -c $<
	$(LD) $(LFLAGS) $(LIBS) $*.o -o $*
clean:
	rm $(PROGS) $(OBJS) $(TEST_OBJS) *.gml

