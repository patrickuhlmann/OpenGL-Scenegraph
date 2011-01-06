#pragma once

#include "NodeVisitor.hpp"
#include <string>

using namespace std;

/**
 * Abstract class representing nodes in the scene graph. It provides basic properties and methods which all nodes have in commen. This is the possibility to accept a NodeVisitor, having a parent and being dirty (need to refresh the values to the children)
 */
class Node {
public:
  virtual ~Node() {
    if (_name)
      delete _name;
  }

  /** \brief Accept a visitor: Usually we call the appropriate method of the Visitor. For a TransformNode this could be visitor->VisitTransform */
  virtual void Accept( NodeVisitor* ) {};

  /** \brief Set the Parent of this Node
  *
  * \param Node* Parent pointer to the parent node
  */
  virtual void SetParent(Node* Parent) {
	_parent = Parent;
  };

  virtual void SetName(string Name) {
    if (_name)
	  delete _name;

	_name = new string(Name);
  }

protected:
  /** \brief Default Constructor sets dirty to false and parent to 0 */
  Node() {
	_dirty = false;
	_parent = 0;
	_name = 0;
  };

  /** \brief Pointer to the Parent Node of this Node */
  Node* _parent;

  string* _name;

  /** \brief If true the children are not refreshed, false otherwise */
  bool _dirty;
};
