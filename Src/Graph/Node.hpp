#pragma once

#include "NodeVisitor.hpp"

/**
 * Abstract class representing nodes in the scene graph.
 * @see NodeVisitor
 */
class Node {
public:

  /** Accept a visitor */
  virtual void Accept( NodeVisitor* ) {};
  // virtual void Add( Node* ) {};
  // virtual void Remove( Node* ) {};

protected:
  /**
   *Construct a default Node.
   * Only subclasses can instatiate a Node.
   */
  Node() : _parent(NULL) {};

  /** 
   * Construct a Node with a pointer to a parent node.
   * Only subclasses can instatiate a Node.
   */
  Node( Node* parent ) : _parent( parent ) {};

  Node* _parent; /**< Pointer to a parent node */

  bool _dirty;
};
