CXX=g++
CFLAGS=-O2 -Wall -g
INCLUDE= -I. \
         -I../pb 
	 
LIB=-lpthread -lprotobuf
VPATH=../pb:./
OUTPUT=test_udp_client
SOURCES= \
	ldbdata.pb.cpp \
	test_udp_client.cpp

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
	rm -f *.o *.~ *.bak a.out
	rm -f $(OUTPUT)

dep:
	mkdep -p$(VPATH) $(INCLUDE) $(SOURCES) > .depend

ifneq ($(wildcard .depend),)
include .depend
endif
