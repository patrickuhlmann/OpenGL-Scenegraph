License:
![GitHub](https://img.shields.io/github/license/patrickuhlmann/opengl-scenegraph)

# OpenGL-Scenegraph

This is work done for a course at the university of Linköping. The aim was to create a small application framework that can be used to render a graph with open GL. It supports Keyhandling, Mesh Loading and Rendering.

## Getting started

### Building

It requires the following libraries to be present:
* google-glog
* freeglut
* glew

Under Archlinux they can be installed with the following command:
```
sudo pacman -S google-glog freeglut glew
```
(at the time of this writing it installed google-glog-0.4.2, freeglut-3.2.1 and glew 2.2.0)

To execute the build, run the following command:
```
make
```

It will create these 6 applications:
* AddRemoveChild: adds rectangles until it reaches 10, then removes until none is left and repeats
* ObjectsLoader: loads several meshes (rocket, airplane, fighter, gambling machine, soccer ball, rose)
* PongGame: the famous pong game
* SimpleGeometry: a ring, a sphere and a cube
* SkeletonApp: similar to objectsloader
* TestGraphApp: uses Render visitors to transform a building, a vase and a flower

### Documentation

This requires doxygen.

Under Archlinux it can be installed with the following command:
```
sudo pacman -S 
```

To create the documentation, run the following command:
```
make doc
```

You will find the generated documentation under doc/html/index.html

In the folder Docs there is also some documentation that doesn't need to be generated. It is recommended to start with Docs/Getting_Started.doc
