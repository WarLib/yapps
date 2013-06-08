#
# Makfile für YAPPS

# Compiler Settings
CC=g++
CFLAGS= `pkg-config --cflags OGRE OIS`
LDFLAGS= `pkg-config  --libs OGRE OIS`
FOLDERS=$(shell  find . -type d -path './[!.]*')
INCLUDE_FOLDERS=$(addprefix -I,$(patsubst %,%/,$(FOLDERS)))
SOURCES=$(shell  find . -name '*.cpp' -not -name '*testing*')
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

