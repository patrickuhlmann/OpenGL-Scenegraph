#pragma once

class NodeVisitor {
public:
  // default implementation does nothing
  virtual void VisitTransform( Transform* ) {};
  virtual void VisitGeometry ( Geometry* )  {};
  virtual void VisitLight    ( Light* )     {};
  virtual void VisitGroup    ( Group* )     {};
  virtual void VisitCamera   ( Camera* )    {};

protected:
  NodeVisitor() {}; // abstract

private:
  virtual void Traverse( CompositeNode* c );

};
