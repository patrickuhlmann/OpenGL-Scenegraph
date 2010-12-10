CXX = c++
CXXFLAGS = -pg -g
CXXTESTFLAGS = -lgtest -pthread -lglog
LDFLAGS = -L/usr/X11R6/lib -lglut -lGLU -lGL -lXmu -lX11 -lm -pg -g -lglog

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

TestMeshLoaders: Tests/TestMeshLoaders.cpp MeshLoader.o MeshFileLoader.o MeshLoaderObj.o Mesh.o math3d.o
	$(CXX) $(CXXFLAGS) $(CXXTESTFLAGS) Tests/TestMeshLoaders.cpp math3d.o Mesh.o MeshLoader.o MeshFileLoader.o MeshLoaderObj.o -o Tests/TestMeshLoaders
	./Tests/TestMeshLoaders

MeshLoader.o: Src/MeshLoaders/MeshLoader.cpp Src/MeshLoaders/MeshLoader.h
	$(CXX) -c $(CXXFLAGS) Src/MeshLoaders/$*.cpp

MeshFileLoader.o: MeshLoader.o Src/MeshLoaders/MeshFileLoader.cpp Src/MeshLoaders/MeshFileLoader.h
	$(CXX) -c $(CXXFLAGS) Src/MeshLoaders/$*.cpp

MeshLoaderObj.o: Src/MeshLoaders/IMeshLoader.h Src/MeshLoaders/MeshLoaderObj.cpp Src/MeshLoaders/MeshLoaderObj.h
	$(CXX) -c $(CXXFLAGS) Src/MeshLoaders/$*.cpp

Mesh.o: Src/Base/Mesh.cpp Src/Base/Mesh.hpp
	$(CXX) -c $(CXXFLAGS) Src/Base/$*.cpp

math3d.o: Src/Include/math3d.h Src/Include/math3d.cpp
	$(CXX) -c $(CXXFLAGS) Src/Include/$*.cpp




