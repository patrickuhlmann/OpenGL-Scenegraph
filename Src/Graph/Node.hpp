#pragma once

#include <glog/logging.h>
#include "NodeVisitor.hpp"
#include <string>

using namespace std;

/**
 * Abstract class representing nodes in the scene graph. It provides basic properties and methods which all nodes have in commen. This is the possibility to accept a NodeVisitor, having a parent, a name and being dirty (need to refresh the values to the children)
 */
class Node {
public:
  /** \brief Destructor. free name */
  virtual ~Node() {
    if (_name)
      delete _name;
  }

  /** \brief Accept a visitor: Usually we call the appropriate method of the Visitor. For a TransformNode this could be visitor->VisitTransform */
  virtual void Accept( NodeVisitor* ) {};

  /** \brief Set the Parent of this Node. You cannot set yourself as parent
  *
  * \param Node* Parent pointer to the parent node
  */
  virtual void SetParent(Node* Parent) {
	if (Parent == this)
		return;

	_parent = Parent;
  };

  /** \brief Get the Parent of this Node. It can also be 0 when there is no parent */
  virtual Node* GetParent() const {
	return _parent;
  }

  /** \brief Set the name of this node
  *
  * \param string Name of the node
  */
  virtual void SetName(const string Name) {
    if (_name)
	  delete _name;

	_name = new string(Name);
  }

  /** \brief Get the Name of this node. If it had no name "" will be returned */
  virtual string GetName() const {
	if (_name)
		return *_name;
	else
		return "";
  }
  

protected:
  /** \brief Default Constructor sets dirty to false and parent to 0 */
  Node() {
	_dirty = false;
	_parent = 0;
	_name = 0;
  };

  /** \brief Creates a node with the specified name which is not dirty and has no parent */
  Node(string name) {
	_dirty = false;
	_parent = 0;
	_name = new string(name);
  };

  /** \brief Pointer to the Parent Node of this Node */
  Node* _parent;

  /** \brief Pointer to the Name of this Node */
  string* _name;

  /** \brief If true the children are not refreshed, false otherwise */
  bool _dirty;
};
