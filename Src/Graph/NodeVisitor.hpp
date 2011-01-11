#pragma once

#ifdef MEMORY_CHECK_ACTIVE
	#include "../../Libs/nvwa-0.8.2/debug_new.h"
#endif

class Node;
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
   virtual void Visit( Node* ) = 0;
   virtual void VisitTransform( Transform* ) = 0;
   virtual void VisitGeometry ( Geometry* )  = 0;
   virtual void VisitLight    ( Light* )     = 0;
   virtual void VisitGroup    ( Group* )     = 0;
   virtual void VisitCamera   ( Camera* )    = 0;
   /** \brief Destructor. Empty */
   virtual ~NodeVisitor() { };
   
protected:
   /** Only subclasses can construct a NodeVisitor */
   NodeVisitor() {}; // abstract
};
