#pragma once

#include "Node.hpp"
#include <list>
#include <algorithm>
#include <iostream>

typedef std::list< Node* > NodeList;
typedef NodeList::iterator NodeIterator;

/** \brief This is a abstract base class for all nodes that can have children. It provides methods to Add and Remove children as well as searching for them */
class CompositeNode : public Node {
public:
  /** \brief Delete all the Children */
  virtual ~CompositeNode() {
	for (NodeIterator it = _children.begin(); it != _children.end(); it++) {
	  delete *it;
	}
  }

  /** \brief Accept a visitor: Usually we call the appropriate method of the Visitor. For a TransformNode this could be visitor->VisitTransform
   * \param Visitor for the Node
   */
  virtual void Accept( NodeVisitor* Visitor ) = 0;

  /** \brief Add a Node as Child. This method will automatically set this node as the parent of the child.
  * If it had another parent before it will remove the node from that Parent (so the node will always just
  * be at the place where it was added the last
  *
  * \param n to add as child
  * \param return point to itself for easy call chaining
  */
  CompositeNode* AddChild( Node* n ) {
	if (n->GetParent() != 0)
		DLOG(WARNING) << "Node has already a parent!" << endl;

	n->SetParent(this);
	_children.push_back( n ); 

	return this;
  };


/* TODO: Override SetParent and make it add this as a child in the parent node */

  /** \brief Remove a Node as a Child. If we don't have this node nothing at all happens. If we have the node it will be removed and deleted */
  virtual void RemoveChild(Node* n) {
	int SizeBefore = _children.size();
	_children.remove(n);

	if (_children.size() < SizeBefore)
		delete n;
  };

  /** \brief Remove a Node as a Child. If we don't have this node nothing at all happens. It we have the node it will be removed and it's parent is set to 0 */
  virtual void RemoveChild(const string& Name) {
	int SizeBefore = _children.size();

	Node* n = 0;
    for (NodeIterator it=_children.begin(); it != _children.end(); it++) {
		// Check if it is the right one
		if ((*it)->GetName() == Name) {
			n = *it;
			break;
		}
	}

	if (!n)
		DLOG(WARNING) << "Node " << Name << " not found" << endl;

	_children.remove(n);

	if (_children.size() < SizeBefore)
		delete n;
  };

  /** \brief Gets a iterator pointing to the very first element of the children list. */  
  virtual NodeIterator GetNodeIterator() { return _children.begin(); };

  /** \brief Get a iterator pointing after the very last element of the children list */
  virtual NodeIterator GetNodeIteratorEnd() { return _children.end(); };

  /** \brief Return true if one of the children is the Node, false otherwise */
  virtual bool Contains(Node* n) {
	return find(_children.begin(), _children.end(), n) != _children.end();
  }

  /** \brief Return how many children this node has */
  virtual int GetChildrenCount() {
	return _children.size();
  }

  /** \brief Try to find a node by Name. It will check it's own name, the names of the children and even traverse all the children to see if they can find the node. If it finds a suiting node it returns a pointer to it, otherwise it returns false */
  virtual Node* GetByName(const string& Name) {
    if (this->GetName() == Name)
       return this;

    for (NodeIterator it=_children.begin(); it != _children.end(); it++) {
		// If CompositeNode execute another lookup for the name
		if (reinterpret_cast<CompositeNode*>((*it))) {
			CompositeNode* n = reinterpret_cast<CompositeNode*>(*it);
			Node* FoundN = n->GetByName(Name);
			if (FoundN)
				return FoundN;
		} else {
			// Check if it is the right one
			if ((*it)->GetName() == Name)
				return (*it);
		}
	}

    return 0;
  }

  virtual void PrintChildren(ostream& out) {
	out << "Children for: " << this->GetName() << "[";
    for (NodeIterator it=_children.begin(); it != _children.end(); it++) {
		out << "(" << (*it)->GetName() << ")";
	}
	out << "]" << endl;
  }

  virtual void PrintWholeTree(ostream& out) {
	out << "Children for: " << this->GetName() << "[";
    for (NodeIterator it=_children.begin(); it != _children.end(); it++) {
		out << "(" << (*it)->GetName() << ")";

		if (reinterpret_cast<CompositeNode*>((*it))) {
			if (CompositeNode* n = reinterpret_cast<CompositeNode*>((*it)))
		  		n->PrintChildren(out);
		}
	}
	out << "]" << endl;
  }

protected:
  /** \brief This constructor does nothing and is protected to prevent instating the abstract class */
  CompositeNode() : Node() {};

  /** \brief This constructor creates a node with a name, it's protected to prevent instating the abstract class */
  CompositeNode(const string& Name) : Node(Name) { };

  /** \brief To hold the child nodes */
  NodeList _children; 
};
