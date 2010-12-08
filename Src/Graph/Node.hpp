#pragma once



class Node {
public:
  virtual void Accept( NodeVisitor* ) {};
  // virtual void Add( Node* ) {};
  // virtual void Remove( Node* ) {};

protected:
   Node() : _parent(NULL) {};
   Node( Node* parent ) : _parent( parent ) {};
   Node* _parent;
};
