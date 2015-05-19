CXX=g++
CFLAGS=-O2 -Wall -g
INCLUDE= -I../ldbserver \
	 -I../Command \
	 -I../pb 
	 
LIB=-lleveldb -lpthread -lprotobuf -lev
VPATH=../ldbserver:../Command:../pb:./
OUTPUT=test_udp_server
SOURCES= \
        test_udp_server.cpp \
	Command.cpp \
	OpenCommand.cpp \
	GetCommand.cpp  \
	PutCommand.cpp \
	DeleteCommand.cpp \
	ldbdata.pb.cpp \
	ldbserver.cpp \
	ldbudpserver.cpp

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
