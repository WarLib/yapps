#
# Makfile für YAPPS

# Compiler Settings
CC=g++
CFLAGS=-Wall -g -I$(OGRE_LOC) -I$(OIS_LOC)
LDFLAGS= -lOgreMain -lOIS
FOLDERS=$(shell  find . -type d -path './[!.]*')
INCLUDE_FOLDERS=$(addprefix -I,$(patsubst %,%/,$(FOLDERS)))
SOURCES=$(shell  find . -name '*.cpp')
#SOURCES=$(wildcard *.cpp) $(wildcard */*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)

P_YAPPS=yapps

#rules
all: $(P_YAPPS)

$(P_YAPPS): $(OBJECTS)
	$(CC) -o $@ $+ $(LDFLAGS)
	
# generic rule for compiling *.cpp -> *.o
%.o: %.cpp
	$(CC) -c $*.cpp -o $@ $(INCLUDE_FOLDERS)  $(CFLAGS) 

clean:
	rm -f $(OBJECTS)
	rm -f $(P_YAPPS)

rebuild: clean all

