#pragma once

#include <glog/logging.h>
#include "NodeVisitor.hpp"
#include <string>

#ifdef MEMORY_CHECK_ACTIVE
	#include "../../Libs/nvwa-0.8.2/debug_new.h"
#endif

using namespace std;

/**
 * Abstract class representing nodes in the scene graph. It provides basic properties and methods which all nodes have in common. This is the possibility to accept a NodeVisitor, having a parent and a name
 */
class Node {
public:
  virtual ~Node();

  /** \brief Accept a visitor: Usually we call the appropriate method of the Visitor. For a TransformNode this could be visitor->VisitTransform
   * \param Visitor for the Node
   */
  virtual void Accept( NodeVisitor* Visitor ) = 0;

  virtual const Node* GetParent() const;

  virtual const string& GetName() const;

  void SetParent(Node* Parent);
  
protected:
	Node();
	Node(string name);

	/** \brief Pointer to the Parent Node of this Node */
	Node* _parent;

	/** \brief Pointer to the Name of this Node */
	string _name;

	static int NodeCounter;
};
