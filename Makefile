CXX = c++
CXXFLAGS = -pg -g
CXXTESTFLAGS = -lgtest -pthread -lglog
LDFLAGS = -L/usr/X11R6/lib -lglut -lGLU -lGL -lXmu -lX11 -lm -pg -g -lglog -lGLEW
LDFLAGSAPPLE = -lm  -pg -g -lglog -framework OpenGL -framework GLUT /opt/local/lib/libGLEW.a
GRAPHICPROGO = SimpleApplication.o BaseApplication.o BaseApplicationInstanceInit.o InputManager.o InputManagerInstanceInit.o GLTools.o MeshFileLoader.o MeshLoaderObj.o MeshLoader.o Mesh.o Material.o math3d.o Light.o Camera.o RenderVisitorOpenGL1.o Transform.o Geometry.o State.o GLBatch.o GLTriangleBatch.o OpenGLDrawing.o OpenGLState.o Group.o Datatypes.o OpenGLFixedAdapter.o Cube.o Torus.o Sphere.o
#Libs/nvwa-0.8.2/debug_new.o

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
	rm -rf Tests/TestCompositeNode
	rm -rf Tests/TestNode
	rm -rf gmon.out
	rm -rf SkeletonApp

doc:
	doxygen Doxyfile

AllCode: UpdateVisitor.o Transform.o Light.o Geometry.o Camera.o SkeletonApp SkeletonApp.o SimpleApplication.o BaseApplicationInstanceInit.o BaseApplication.o InputManagerInstanceInit.o InputManager.o State.o Material.o GLTriangleBatch.o GLTools.o GLShaderManager.o GLBatch.o math3d.o Mesh.o MeshLoaderObj.o MeshFileLoader.o MeshLoader.o RenderVisitorOpenGL1.o OpenGLDrawing.o OpenGLState.o Group.o Datatypes.o OpenGLFixedAdapter.o Cube.o Torus.o Sphere.o SimpleGeometry.o SimpleGeometry ObjectsLoader.o ObjectsLoader

AllTests: TestMeshLoaders TestNode TestCompositeNode

TestMeshLoaders: Tests/TestMeshLoaders.cpp MeshLoader.o MeshFileLoader.o MeshLoaderObj.o Mesh.o math3d.o Material.o
	$(CXX) $(CXXFLAGS) $(CXXTESTFLAGS) Tests/TestMeshLoaders.cpp math3d.o Mesh.o MeshLoader.o MeshFileLoader.o MeshLoaderObj.o Material.o -o Tests/TestMeshLoaders
	./Tests/TestMeshLoaders

TestNode: Tests/TestNode.cpp Src/Graph/Node.hpp
	$(CXX) $(CXXFLAGS) $(CXXTESTFLAGS) Tests/TestNode.cpp -o Tests/TestNode
	./Tests/TestNode

TestCompositeNode: Tests/TestCompositeNode.cpp Src/Graph/Node.hpp Src/Graph/CompositeNode.hpp
	$(CXX) $(CXXFLAGS) $(CXXTESTFLAGS) Tests/TestCompositeNode.cpp -o Tests/TestCompositeNode
	./Tests/TestCompositeNode

MeshLoader.o: Src/MeshLoaders/MeshLoader.cpp Src/MeshLoaders/MeshLoader.h
	$(CXX) -c $(CXXFLAGS) Src/MeshLoaders/$*.cpp

MeshFileLoader.o: MeshLoader.o Src/MeshLoaders/MeshFileLoader.cpp Src/MeshLoaders/MeshFileLoader.h
	$(CXX) -c $(CXXFLAGS) Src/MeshLoaders/$*.cpp

Cube.o: Src/Base/Geometry/Cube.cpp Src/Base/Geometry/Cube.h
	$(CXX) -c $(CXXFLAGS) Src/Base/Geometry/$*.cpp

Sphere.o: Src/Base/Geometry/Sphere.cpp Src/Base/Geometry/Sphere.h
	$(CXX) -c $(CXXFLAGS) Src/Base/Geometry/$*.cpp

OpenGLFixedAdapter.o: Src/Graphics/Adapter/OpenGLFixedAdapter.cpp Src/Graphics/Adapter/OpenGLFixedAdapter.h Src/Graphics/Adapter/GraphicsAdapter.h
	$(CXX) -c $(CXXFLAGS) Src/Graphics/Adapter/$*.cpp

MeshLoaderObj.o: Src/MeshLoaders/IMeshLoader.h Src/MeshLoaders/MeshLoaderObj.cpp Src/MeshLoaders/MeshLoaderObj.h Src/Base/Datatypes.cpp Src/Base/Datatypes.h
	$(CXX) -c $(CXXFLAGS) Src/MeshLoaders/$*.cpp

Mesh.o: Src/Base/Mesh.cpp Src/Base/Mesh.hpp
	$(CXX) -c $(CXXFLAGS) Src/Base/$*.cpp

Datatypes.o: Src/Base/Datatypes.cpp Src/Base/Datatypes.h
	$(CXX) -c $(CXXFLAGS) Src/Base/$*.cpp

math3d.o: Src/Include/math3d.h Src/Include/math3d.cpp
	$(CXX) -c $(CXXFLAGS) Src/Include/$*.cpp

GLBatch.o: Src/Include/GLBatch.cpp
	$(CXX) -c $(CXXFLAGS) Src/Include/$*.cpp

GLShaderManager.o: Src/Include/GLShaderManager.cpp
	$(CXX) -c $(CXXFLAGS) Src/Include/$*.cpp

GLTools.o: Src/Include/GLTools.cpp
	$(CXX) -c $(CXXFLAGS) Src/Include/$*.cpp

GLTriangleBatch.o: Src/Include/GLTriangleBatch.cpp
	$(CXX) -c $(CXXFLAGS) Src/Include/$*.cpp

Material.o: Src/Base/Material.cpp Src/Base/Material.hpp
	$(CXX) -c $(CXXFLAGS) Src/Base/$*.cpp

State.o: Src/Base/State.cpp Src/Base/State.hpp
	$(CXX) -c $(CXXFLAGS) Src/Base/$*.cpp

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

SimpleGeometry.o: Src/Showcase/SimpleGeometry.cpp Src/Showcase/SimpleGeometry.h
	$(CXX) -c $(CXXFLAGS) Src/Showcase/$*.cpp

SimpleGeometry: Src/Showcase/SimpleGeometry.cpp $(GRAPHICPROGO) SimpleGeometry.o
	$(CXX) $(GRAPHICPROGO) SimpleGeometry.o -o SimpleGeometry $(LDFLAGS)

ObjectsLoader.o: Src/Showcase/ObjectsLoader.cpp Src/Showcase/ObjectsLoader.h
	$(CXX) -c $(CXXFLAGS) Src/Showcase/$*.cpp

ObjectsLoader: Src/Showcase/ObjectsLoader.cpp $(GRAPHICPROGO) ObjectsLoader.o
	$(CXX) $(GRAPHICPROGO) ObjectsLoader.o -o ObjectsLoader $(LDFLAGS)

Camera.o: Src/Graph/Camera.cpp Src/Graph/Camera.hpp
	$(CXX) -c $(CXXFLAGS) Src/Graph/$*.cpp

Group.o: Src/Graph/Group.cpp Src/Graph/Group.hpp
	$(CXX) -c $(CXXFLAGS) Src/Graph/$*.cpp

Geometry.o: Src/Graph/Geometry.cpp Src/Graph/Geometry.hpp
	$(CXX) -c $(CXXFLAGS) Src/Graph/$*.cpp

Light.o: Src/Graph/Light.cpp Src/Graph/Light.hpp
	$(CXX) -c $(CXXFLAGS) Src/Graph/$*.cpp

RenderVisitorOpenGL1.o: Src/Graph/RenderVisitorOpenGL1.cpp Src/Graph/RenderVisitorOpenGL1.hpp
	$(CXX) -c $(CXXFLAGS) Src/Graph/$*.cpp

RenderVisitorOpenGL2.o: Src/Graph/RenderVisitorOpenGL2.cpp Src/Graph/RenderVisitorOpenGL2.hpp
	$(CXX) -c $(CXXFLAGS) Src/Graph/$*.cpp

Transform.o: Src/Graph/Transform.cpp Src/Graph/Transform.hpp
	$(CXX) -c $(CXXFLAGS) Src/Graph/$*.cpp

UpdateVisitor.o: Src/Graph/UpdateVisitor.cpp Src/Graph/UpdateVisitor.hpp
	$(CXX) -c $(CXXFLAGS) Src/Graph/$*.cpp

TransformUpdateVisitor.o: Src/Graph/TransformUpdateVisitor.cpp Src/Graph/TransformUpdateVisitor.hpp
	$(CXX) -c $(CXXFLAGS) Src/Graph/$*.cpp

UpdateVisitorFactory.o: Src/Graph/UpdateVisitorFactory.cpp Src/Graph/UpdateVisitorFactory.hpp
	$(CXX) -c $(CXXFLAGS) Src/Graph/$*.cpp

TransformStrategy.o: Src/Graph/TransformStrategy.cpp Src/Graph/TransformStrategy.hpp
	$(CXX) -c $(CXXFLAGS) Src/Graph/$*.cpp

TranslateTransformStrategy.o: Src/Graph/TranslateTransformStrategy.cpp Src/Graph/TranslateTransformStrategy.hpp
	$(CXX) -c $(CXXFLAGS) Src/Graph/$*.cpp

ScaleTransformStrategy.o: Src/Graph/ScaleTransformStrategy.cpp Src/Graph/ScaleTransformStrategy.hpp
	$(CXX) -c $(CXXFLAGS) Src/Graph/$*.cpp

RotateTransformStrategy.o: Src/Graph/RotateTransformStrategy.cpp Src/Graph/RotateTransformStrategy.hpp
	$(CXX) -c $(CXXFLAGS) Src/Graph/$*.cpp

OpenGLDrawing.o: Src/OpenGLFixed/OpenGLDrawing.cpp Src/OpenGLFixed/OpenGLDrawing.h
	$(CXX) -c $(CXXFLAGS) Src/OpenGLFixed/$*.cpp

OpenGLDrawing.o: Src/Graphics/OpenGLFixed/OpenGLDrawing.cpp Src/Graphics/OpenGLFixed/OpenGLDrawing.h
	$(CXX) -c $(CXXFLAGS) Src/Graphics/OpenGLFixed/$*.cpp

OpenGLState.o: Src/Graphics/OpenGLFixed/OpenGLState.cpp Src/Graphics/OpenGLFixed/OpenGLState.h
	$(CXX) -c $(CXXFLAGS) Src/Graphics/OpenGLFixed/$*.cpp

Torus.o: Src/Base/Geometry/Torus.cpp Src/Base/Geometry/Torus.h
	$(CXX) -c $(CXXFLAGS) Src/Base/Geometry/$*.cpp
