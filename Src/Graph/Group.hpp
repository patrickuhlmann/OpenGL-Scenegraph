#pragma once

#include "CompositeNode.hpp"
#include "NodeVisitor.hpp"
#include "State.hpp"

/**
 * Goups several graph nodes together spatially.
 * A group can hold a number of children in a scene graph.
 * The group can be used to create subgraphs of related nodes.
 */
class Group : public CompositeNode {
public:

  Group( Node* parent ) : CompositeNode( parent ) {};
  
  virtual void Accept( NodeVisitor* );

  void SetState( const State& );

  
private:
  State _state;
};
