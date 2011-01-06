#pragma once

#include <list>
#include "Node.hpp"

typedef std::list< Node* > NodeList;
typedef NodeList::iterator NodeIterator;

class CompositeNode : public Node {
public:
  virtual Node* GetByName(string Name) {
    /*if (this->_name == Name)
       return this;

    NodeIterator it;
    for (it=_children.begin(); it != _children.end(); it++) {
		if ((*it)->_name == Name)
		  return *it;
	}*/

    return 0;
  }

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
