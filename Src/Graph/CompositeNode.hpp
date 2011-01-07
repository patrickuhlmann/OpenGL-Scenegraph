#pragma once

#include <list>
#include <algorithm>
#include "Node.hpp"

typedef std::list< Node* > NodeList;
typedef NodeList::iterator NodeIterator;

/** \brief This is a abstract base class for all nodes that can have children. It provides methods to Add and Remove children as well as searching for them */
class CompositeNode : public Node {
public:
  /** \brief Delete all the Children */
  ~CompositeNode() {
	for (NodeIterator it = _children.begin(); it != _children.end(); it++) {
	  delete *it;
	}
  }

  /** \brief Add a Node as Child. This method will automatically set this node as the parent of the child.
  * If it had another parent before it will remove the node from that Parent (so the node will always just
  * be at the place where it was added the last
  *
  * \param n to add as child
  */
  virtual void AddChild( Node* n ) {
    if (n->GetParent())
		reinterpret_cast<CompositeNode*>(n->GetParent())->RemoveChild(n);

	n->SetParent(this);
	_children.push_back( n ); 
        //DLOG(INFO) << "Children count: " << _children.size() << endl;
  };

  /** \brief Remove a Node as a Child. If we don't have this node nothing at all happens. It we have the node it will be removed and it's parent is set to 0 */
  virtual void RemoveChild( Node* n ) {
	int SizeBefore = _children.size();
	_children.remove(n);

	if (_children.size() < SizeBefore)
		n->SetParent(0);
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

    NodeIterator it;
    for (it=_children.begin(); it != _children.end(); it++) {
		if (reinterpret_cast<CompositeNode*>((*it))) {
			if (Node* n = reinterpret_cast<CompositeNode*>((*it))->GetByName(Name))
		  		return n;
		}
	}

    return 0;
  }

protected:
  /** \brief This constructor does nothing and is protected to prevent instating the abstract class */
  CompositeNode() : Node() {};

  /** \brief This constructor creates a node with a name, it's protected to prevent instating the abstract class */
  CompositeNode(string name) : Node(name) { };

  /** \brief To hold the child nodes */
  NodeList _children; 
};
