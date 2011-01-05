#pragma once

#include <list>
#include "Node.hpp"

typedef std::list< Node* > NodeList;
typedef NodeList::iterator NodeIterator;

class CompositeNode : public Node {
public:
  virtual void Add( Node* n )    {
	n->SetParent(this);
	_children.push_back( n ); 
  };

  virtual void Remove( Node* n ) { 
	n->SetParent(0);
	_children.remove( n ); 
  };

  virtual NodeIterator GetNodeIterator() { return _children.begin(); };
  virtual NodeIterator GetNodeIteratorEnd() { return _children.end(); };

protected:
  CompositeNode() {};
  NodeList _children; 
};
