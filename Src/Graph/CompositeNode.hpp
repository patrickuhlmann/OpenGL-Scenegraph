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
  *
  * \param n to add as child
  * \param return point to itself for easy call chaining
  */
  CompositeNode* AddChild( Node* n ) {
	if (n->GetParent() != 0)
		LOG(WARNING) << "Node has already a parent!" << endl;

	n->SetParent(this);
	_children.push_back( n ); 

	return this;
  }

  /** \brief Remove a Node as a Child. If we don't have this node nothing at all happens. If we have the node it will be removed and deleted. You cannot use it anymore!
   * \param n Node to remove
   * \return true if we found a child and removed it, false otherwise */
  virtual bool RemoveChild(Node* n) {
	int SizeBefore = _children.size();
	_children.remove(n);

	if (_children.size() < SizeBefore) {
		delete n;
		return true;
	} else {
		LOG(WARNING) << "Node didn't have Children!" << endl;
		return false;
	}
  }

  /** \brief Remove a Node as a Child. If we don't have this node nothing at all happens. It we have the node it will be removed and deleted. You cannot use it anymore
	* \return true if we found a suiting node and removed it, false otherwise */
  virtual bool RemoveChild(const string& Name) {
/** TODO: write with remove_if or find!!!! */
	Node* n = 0;
    for (NodeIterator it=_children.begin(); it != _children.end(); it++) {
		// Check if it is the right one
		if ((*it)->GetName() == Name) {
			n = *it;
			break;
		}
	}

	if (!n) {
		DLOG(WARNING) << "Node " << Name << " not found" << endl;
		return false;
	} else {
		_children.remove(n);
		delete n;
		return true;
	}
  };

  /** \brief Gets a iterator pointing to the very first element of the children list. */  
  virtual NodeIterator GetNodeIterator() {
	return _children.begin();
  };

  /** \brief Get a iterator pointing after the element after the very last element of the children list */
  virtual NodeIterator GetNodeIteratorEnd() {
	return _children.end();
  };

  /** \brief Check if a Node is one of our children
    * \param n to search for
    * \return true if found, false otherwise */
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

	//LOG(WARNING) << "Couldn't find the Node " << Name << endl;

    return 0;
  }

  /** \brief Utility Method to Print the Name of all children to a stream
   * \param out Stream to print to
   */
  // TODO: with for_each
  virtual void PrintChildren(ostream& out) {
	out << "Children for: " << this->GetName() << "[";
    for (NodeIterator it=_children.begin(); it != _children.end(); it++) {
		out << "(" << (*it)->GetName() << ")";
	}
	out << "]" << endl;
  }

  /** \brief Utility Method to Print the whole tree (children and then their children etc.) to a stream
   * \param out Stream to print to
   */
  // TODO: nicer output?
  // TODO: with for_each ev. using PrintChildren
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
