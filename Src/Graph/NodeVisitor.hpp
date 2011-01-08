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
   virtual void VisitTransform( Transform* ) = 0;
   virtual void VisitGeometry ( Geometry* )  = 0;
   virtual void VisitLight    ( Light* )     = 0;
   virtual void VisitGroup    ( Group* )     = 0;
   virtual void VisitCamera   ( Camera* )    = 0;

   virtual void Traverse( CompositeNode* c ) = 0;

protected:
   /** Only subclasses can construct a NodeVisitor */
   NodeVisitor() {}; // abstract

};
