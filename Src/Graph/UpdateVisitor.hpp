#pragma once

#include "NodeVisitor.hpp"
#include "../Include/math3d.h"
#include "../Base/State.hpp"
#include "../Base/Material.hpp"

/**
 * Updates a node in the scene graph.
 * The visitor has members that can be used to update
 * or set the values of nodes in the graph.
 * If a member corresponding to a valid setting on the 
 * visited node has a non-zero value it will update it.
 */
class UpdateVisitor : public NodeVisitor {
public:
  UpdateVisitor();
  ~UpdateVisitor();
  
  /**
   * Update a transform node.
   *
   * Update a transform node by replacing it's
   * current transformation matrix with the visitor's.
   *
   * @see Transform.
   * @param t Node to visit
   */
  virtual void VisitTransform( Transform* );

  /**
   * 
   * @see Geometry
   * @param g Node to visit  
   */
  virtual void VisitGeometry( Geometry* );

  /**
   * Update the light with new values.
   *
   * The values are given by the visitor's members
   * applicable to the light node.
   *
   * @see Light
   * @param l Node to visit   
   */
  virtual void VisitLight( Light* );

  /**
   * Visit a group having a number of children.
   *
   * @see Group
   * @param g Node to visit  
   */
  virtual void VisitGroup( Group* );

  /**
   * Get transformations for viewing space and projection.
   * Retrieve the view matrix and projection load them to
   * the matrix stacks. View and projection transforms aren't
   * accumulated.
   *
   * @see Camera
   * @param c Node to Visit
   */
  virtual void VisitCamera( Camera* );
  
  void SetTransform( const M3DMatrix44f& );
  void SetDirection( const M3DVector3f& );
  void SetPosition( const M3DVector3f& );
  void SetState( State* );
  void SetMaterial ( const Material& );

private:

  /**
   * Traverse a composite.
   * @param c Node to Traverse
   * @see CompositeNode
   */
  virtual void Traverse( CompositeNode* c );

  M3DMatrix44f _transform;
  M3DVector3f  _direction;
  M3DVector3f  _position;
  Material*     _material;
  State* _state;
  //  Texture* _texture;
};
