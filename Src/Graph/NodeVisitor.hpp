#pragma once

class CompositeNode;
class Light;
class Group;
class Transform;
class Geometry;
class Camera;

/**
 * Abstract class used for visiting scenegraph nodes.
 */ 
class NodeVisitor {
public:
   // default implementation does nothing
   virtual void VisitTransform( Transform* ) {};
   virtual void VisitGeometry ( Geometry* )  {};
   virtual void VisitLight    ( Light* )     {};
   virtual void VisitGroup    ( Group* )     {};
   virtual void VisitCamera   ( Camera* )    {};

   virtual void Traverse( CompositeNode* c ) {};

protected:
   /** Only subclasses can construct a NodeVisitor */
   NodeVisitor() {}; // abstract

};
