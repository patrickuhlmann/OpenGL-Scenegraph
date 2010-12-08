#pragma once

#include <list>
#include "Node.hpp"

typedef std::list< Node* > NodeList;
typedef NodeList::iterator NodeIterator;

class CompositeNode : public Node {
public:
  virtual void Add( Node* )    { _children.push_back( n ); };
  virtual void Remove( Node* ) { _children.remove( n ); };
  virtual NodeIterator GetNodeIterator() { return NodeIterator( _children ); };
  virtual NodeIterator GetNodeIteratorEnd() { return _children.end(); };

protected:
  CompositeNode() {};
  CompositeNode( Node* parent ) : Node( parent ) {};
  NodeList _children; 
};