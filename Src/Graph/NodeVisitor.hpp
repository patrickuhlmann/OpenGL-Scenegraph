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
 * Abstract class interface used for visiting scenegraph nodes. Visit is intended to start the whole visit. All Nodes should then call the appropriate method (TransformNode calls VisitTransform) until it is finished. If you want to do a recursive visit you can call accept for all children of a CompositeNode
 */
class NodeVisitor {
public:
   /** \brief Intended to start the Process */
   virtual void Visit( Node* n ) = 0;
   /** \brief VisitTransform gets all the Transform Nodes and can execute actions on them */
   virtual void VisitTransform( Transform* ) = 0;
   /** \brief VisitGeometry gets all the geometry nodes and can execute actions on them */
   virtual void VisitGeometry ( Geometry* )  = 0;
   /** \brief VisitLight gets all the light nodes and can execute actions on them */
   virtual void VisitLight    ( Light* )     = 0;
   /** \brief VisitGroup gets all the group nodes and can execute actions on them */
   virtual void VisitGroup    ( Group* )     = 0;
   /** \brief VisitCamera gets all the camera nodes and can execute actions on them */
   virtual void VisitCamera   ( Camera* )    = 0;
   /** \brief Destructor. Empty */
   virtual ~NodeVisitor() { };
   
protected:
	/** \brief Only subclasses can construct a NodeVisitor */
	NodeVisitor() {};
};
