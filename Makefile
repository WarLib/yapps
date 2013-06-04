#
# Makfile für YAPPS

# Compiler Settings
CC=g++
CFLAGS=-Wall -g -I$OGRE_LOC -I$OIS_LOC
LDFLAGS = -lOgreMain -lOIS
OBJECTS=

P_YAPPS=yapps

#rules
all: $(P_YAPPS)

$(P_YAPPS): $(OBJECTS)
	$(CC) -o $@ $+ $(LDFLAGS)
	
# generic rule for compiling *.cpp -> *.o
%.o: %.cpp
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $*.cpp

clean:
	rm -f $(OBJECTS)
	rm -f $(P_YAPPS)

rebuild: clean all

