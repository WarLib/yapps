#
# Makfile für YAPPS

# Compiler Settings
CC=g++
CFLAGS= `pkg-config --cflags OGRE OIS bullet` -Wall -I/usr/local/include -I/usr/local/include/OgreBullet/Dynamics -I/usr/local/include/OGRE -I/usr/local/include/bullet -I/usr/local/include/OgreBullet/ -I/usr/local/include/OgreBullet/Collisions/
LDFLAGS= `pkg-config  --libs OGRE OIS bullet` -lOgreBulletDynamics -lOgreBulletCollisions  -L/usr/local/include/bullet/BulletCollision/CollisionShapes/   -lConvexDecomposition
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

