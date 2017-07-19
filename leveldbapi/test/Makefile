CXX=g++
CFLAGS=-O2 -Wall -g
INCLUDE= -I../ldbapi
LIB=-lleveldb -lpthread 
VPATH=../ldbapi:./
OUTPUT=testldbapi
SOURCES=ldbapi.cpp test.cpp

OBJECTS=$(SOURCES:.cpp=.o)
		  
all:$(OUTPUT) 

.SUFFIXES: .o .cpp
.cpp.o:
	$(CXX) $(CFLAGS) $(INCLUDE) -c $(filter %.cpp, $^) 

.o:
	$(CXX) $(CFLAGS) $(INCLUDE) -o $@ $^

$(OUTPUT): $(OBJECTS)
	$(CXX) $(CFLAGS) -o $(OUTPUT) $^ $(INCLUDE) $(LIB)

clean:
	rm -f *.o *.~ *.bak
	rm -f $(OUTPUT)

dep:
	mkdep -p$(VPATH) $(INCLUDE) $(SOURCES) > .depend

ifneq ($(wildcard .depend),)
include .depend
endif
