CC = g++
CFLAGS = -pg -g -lglog -lgtest
CXXTESTFLAGS = -lgtest -pthread -lglog
LDFLAGS = -L/usr/X11R6/lib -lglut -lGLU -lGL -lXmu -lX11 -lm -pg -g -lglog -lGLEW
LDFLAGSAPPLE = -lm  -pg -g -lglog -framework OpenGL -framework GLUT /opt/local/lib/libGLEW.a

APPLICATION := $(patsubst %.cpp,%.o,$(wildcard Src/Application/*.cpp))
BASE := $(patsubst %.cpp,%.o,$(wildcard Src/Base/*.cpp))
GEOMETRY := $(patsubst %.cpp,%.o,$(wildcard Src/Base/Geometry/*.cpp))
GRAPH := $(patsubst %.cpp,%.o,$(wildcard Src/Graph/*.cpp))
GRAPHICSADAPTER := $(patsubst %.cpp,%.o,$(wildcard Src/Graphics/Adapter/*.cpp))
GRAPHICSOPENGL := $(patsubst %.cpp,%.o,$(wildcard Src/Graphics/OpenGLFixed/*.cpp))
INCLUDE := $(patsubst %.cpp,%.o,$(wildcard Src/Include/*.cpp))
GL := $(patsubst %.cpp,%.o,$(wildcard Src/Include/GL/*.c))
MESHLOADERS := $(patsubst %.cpp,%.o,$(wildcard Src/MeshLoaders/*.cpp))
#SHOWCASE := $(patsubst %.cpp,%.o,$(wildcard Src/Showcase/*.cpp))
#SRC := $(patsubst %.cpp,%.o,$(wildcard Src/*.cpp))

# Make obj for a cpp file
%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

all: AddRemoveChild PongGame SkeletonApp ObjectsLoader SimpleGeometry TestGraphApp

clean:
	rm -rf *.o \
    rm -rf Src/Application/*.o \
    rm -rf Src/Base/*.o \
    rm -rf Src/Graph/*.o \
    rm -rf Src/Graphics/Adapter/*.o \
    rm -rf Src/Graphics/OpenGLFixed/*.o \
    rm -rf Src/Include/*.o \
    rm -rf Src/MeshLoaders/*.o \
    rm -rf Src/Showcase/*.o \
	rm -rf DoxygenWarnings.log
	rm -rf doc/
	rm -rf Tests/TestMeshLoaders
	rm -rf Tests/TestCompositeNode
	rm -rf Tests/TestNode
	rm -rf gmon.out
	rm -rf SkeletonApp
	rm -rf AddRemoveChild
	rm -rf ObjectsLoader
	rm -rf SimpleGeometry
	rm -rf PongGame
	rm -rf TestGraphApp

doc:
	doxygen Doxyfile

AddRemoveChild: $(APPLICATION) $(BASE) $(GEOMETRY) $(GRAPH) $(GRAPHICSADAPTER) $(GRAPHICSOPENGL) $(INCLUDE) $(GL) $(MESHLOADERS) $(SHOWCASE) $(SRC)
	$(CC) $(LDFLAGS) -o AddRemoveChild Src/Showcase/AddRemoveChild.cpp $(APPLICATION) $(BASE) $(GEOMETRY) $(GRAPH) $(GRAPHICSADAPTER) $(GRAPHICSOPENGL) $(INCLUDE) $(GL) $(MESHLOADERS) $(SHOWCASE) $(SRC)

PongGame: $(APPLICATION) $(BASE) $(GEOMETRY) $(GRAPH) $(GRAPHICSADAPTER) $(GRAPHICSOPENGL) $(INCLUDE) $(GL) $(MESHLOADERS) $(SHOWCASE) $(SRC)
	$(CC) $(LDFLAGS) -o PongGame Src/Showcase/PongGame.cpp $(APPLICATION) $(BASE) $(GEOMETRY) $(GRAPH) $(GRAPHICSADAPTER) $(GRAPHICSOPENGL) $(INCLUDE) $(GL) $(MESHLOADERS) $(SHOWCASE) $(SRC)

SkeletonApp: $(APPLICATION) $(BASE) $(GEOMETRY) $(GRAPH) $(GRAPHICSADAPTER) $(GRAPHICSOPENGL) $(INCLUDE) $(GL) $(MESHLOADERS) $(SHOWCASE) $(SRC)
	$(CC) $(LDFLAGS) -o SkeletonApp Src/SkeletonApp.cpp $(APPLICATION) $(BASE) $(GEOMETRY) $(GRAPH) $(GRAPHICSADAPTER) $(GRAPHICSOPENGL) $(INCLUDE) $(GL) $(MESHLOADERS) $(SHOWCASE) $(SRC)

ObjectsLoader: $(APPLICATION) $(BASE) $(GEOMETRY) $(GRAPH) $(GRAPHICSADAPTER) $(GRAPHICSOPENGL) $(INCLUDE) $(GL) $(MESHLOADERS) $(SHOWCASE) $(SRC)
	$(CC) $(LDFLAGS) -o ObjectsLoader Src/Showcase/ObjectsLoader.cpp $(APPLICATION) $(BASE) $(GEOMETRY) $(GRAPH) $(GRAPHICSADAPTER) $(GRAPHICSOPENGL) $(INCLUDE) $(GL) $(MESHLOADERS) $(SHOWCASE) $(SRC)

SimpleGeometry: $(APPLICATION) $(BASE) $(GEOMETRY) $(GRAPH) $(GRAPHICSADAPTER) $(GRAPHICSOPENGL) $(INCLUDE) $(GL) $(MESHLOADERS) $(SHOWCASE) $(SRC)
	$(CC) $(LDFLAGS) -o SimpleGeometry Src/Showcase/SimpleGeometry.cpp $(APPLICATION) $(BASE) $(GEOMETRY) $(GRAPH) $(GRAPHICSADAPTER) $(GRAPHICSOPENGL) $(INCLUDE) $(GL) $(MESHLOADERS) $(SHOWCASE) $(SRC)

TestGraphApp: $(APPLICATION) $(BASE) $(GEOMETRY) $(GRAPH) $(GRAPHICSADAPTER) $(GRAPHICSOPENGL) $(INCLUDE) $(GL) $(MESHLOADERS) $(SHOWCASE) $(SRC)
	$(CC) $(LDFLAGS) -o TestGraphApp Src/TestGraphApp.cpp $(APPLICATION) $(BASE) $(GEOMETRY) $(GRAPH) $(GRAPHICSADAPTER) $(GRAPHICSOPENGL) $(INCLUDE) $(GL) $(MESHLOADERS) $(SHOWCASE) $(SRC)
