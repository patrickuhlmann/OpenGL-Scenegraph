CXX = c++
CXXFLAGS = -pg -g
CXXTESTFLAGS = -lgtest -pthread
LDFLAGS = -L/usr/X11R6/lib -lglut -lGLU -lGL -lXmu -lX11 -lm -pg -g

# Generic rules
.cc.o: $<
	$(CXX) -c $(CXXFLAGS) $*.cpp

.cc: $<
	$(CXX) $(CXXFLAGS) -o $@ $*.cpp $(LDFLAGS)

# Specific
all:
	@echo "This make file support many diffrent functions."
	@echo " make clean -> remove all objects, executable and doxygen documentation directory"
	@echo " make doc -> create the documentation in the doc directory"

clean:
	rm -rf *.o
	rm -rf DoxygenWarnings.log
	rm -rf doc/
	rm -rf Tests/TestMeshLoaders
	rm -rf gmon.out

doc:
	doxygen Doxyfile

TestMeshLoaders: Tests/TestMeshLoaders.cpp
	$(CXX) $(CXXFLAGS) $(CXXTESTFLAGS) Tests/TestMeshLoaders.cpp -o Tests/TestMeshLoaders
	./Tests/TestMeshLoaders

MeshLoader.o: Src/MeshLoaders/IMeshLoader.h Src/MeshLoaders/MeshFileLoader.cpp Src/MeshLoaders/MeshFileLoader.h Src/MeshLoaders/MeshFileLoaderObj.cpp Src/MeshLoaders/MeshFileLoaderObj.h Src/MeshLoaders/MeshLoader.cpp Src/MeshLoaders/MeshLoader.h
	$(CXX) -c $(CXXFLAGS) Src/MeshLoaders/$*.cpp

Mesh.o: Src/Base/Mesh.cpp Src/Base/Mesh.h
	$(CXX) -c $(CXXFLAGS) Src/Base/$*.cpp




