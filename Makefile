CXX = c++
CXXFLAGS = -pg -g
CXXTESTFLAGS = -lgtest -pthread -lglog
LDFLAGS = -L/usr/X11R6/lib -lglut -lGLU -lGL -lXmu -lX11 -lm -pg -g -lglog -lGLEW
GRAPHICPROGO = SimpleApplication.o BaseApplication.o BaseApplicationInstanceInit.o InputManager.o InputManagerInstanceInit.o GLBatch.o GLShaderManager.o GLTriangleBatch.o GLTools.o

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
	rm -rf SkeletonApp

doc:
	doxygen Doxyfile

TestMeshLoaders: Tests/TestMeshLoaders.cpp MeshLoader.o MeshFileLoader.o MeshLoaderObj.o Mesh.o math3d.o Material.o
	$(CXX) $(CXXFLAGS) $(CXXTESTFLAGS) Tests/TestMeshLoaders.cpp math3d.o Mesh.o MeshLoader.o MeshFileLoader.o MeshLoaderObj.o Material.o -o Tests/TestMeshLoaders
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

GLBatch.o: Src/Include/GLBatch.cpp
	$(CXX) -c $(CXXFLAGS) Src/Include/$*.cpp

glew.o: Src/Include/glew.c
	$(CXX) -c $(CXXFLAGS) Src/Include/$*.c

GLShaderManager.o: Src/Include/GLShaderManager.cpp
	$(CXX) -c $(CXXFLAGS) Src/Include/$*.cpp

GLTools.o: Src/Include/GLTools.cpp
	$(CXX) -c $(CXXFLAGS) Src/Include/$*.cpp

GLTriangleBatch.o: Src/Include/GLTriangleBatch.cpp
	$(CXX) -c $(CXXFLAGS) Src/Include/$*.cpp

Material.o: Src/Graph/Material.cpp Src/Graph/Material.hpp
	$(CXX) -c $(CXXFLAGS) Src/Graph/$*.cpp

State.o: Src/Graph/State.cpp Src/Graph/State.hpp
	$(CXX) -c $(CXXFLAGS) Src/Graph/$*.cpp

InputManager.o: Src/Application/InputManager.cpp Src/Application/InputManager.h
	$(CXX) -c $(CXXFLAGS) Src/Application/$*.cpp

InputManagerInstanceInit.o: Src/Application/InputManagerInstanceInit.cpp Src/Application/InputManager.h
	$(CXX) -c $(CXXFLAGS) Src/Application/$*.cpp

BaseApplication.o: Src/Application/BaseApplication.cpp Src/Application/BaseApplication.h
	$(CXX) -c $(CXXFLAGS) Src/Application/$*.cpp

BaseApplicationInstanceInit.o: Src/Application/BaseApplicationInstanceInit.cpp Src/Application/BaseApplication.h
	$(CXX) -c $(CXXFLAGS) Src/Application/$*.cpp

SimpleApplication.o: Src/Application/SimpleApplication.cpp Src/Application/SimpleApplication.h
	$(CXX) -c $(CXXFLAGS) Src/Application/$*.cpp

SkeletonApp.o: Src/SkeletonApp.cpp Src/SkeletonApp.h
	$(CXX) -c $(CXXFLAGS) Src/$*.cpp

SkeletonApp: Src/SkeletonApp.cpp $(GRAPHICPROGO) SkeletonApp.o
	$(CXX) $(GRAPHICPROGO) SkeletonApp.o -o SkeletonApp $(LDFLAGS)

# The following don't work

Camera.o: Src/Graph/Camera.cpp Src/Graph/Camera.hpp
	$(CXX) -c $(CXXFLAGS) Src/Graph/$*.cpp

Geometry.o: Src/Graph/Geometry.cpp Src/Graph/Geometry.hpp
	$(CXX) -c $(CXXFLAGS) Src/Graph/$*.cpp

Group.o: Src/Graph/Group.cpp Src/Graph/Group.hpp
	$(CXX) -c $(CXXFLAGS) Src/Graph/$*.cpp

Light.o: Src/Graph/Light.cpp Src/Graph/Light.hpp
	$(CXX) -c $(CXXFLAGS) Src/Graph/$*.cpp

RenderVisitor.o: Src/Graph/RenderVisitor.cpp Src/Graph/RenderVisitor.hpp
	$(CXX) -c $(CXXFLAGS) Src/Graph/$*.cpp

Transform.o: Src/Graph/Transform.cpp Src/Graph/Transform.hpp
	$(CXX) -c $(CXXFLAGS) Src/Graph/$*.cpp

UpdateVisitor.o: Src/Graph/UpdateVisitor.cpp Src/Graph/UpdateVisitor.hpp
	$(CXX) -c $(CXXFLAGS) Src/Graph/$*.cpp





