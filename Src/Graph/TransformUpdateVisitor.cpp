#include "TransformUpdateVisitor.hpp"

TransformUpdateVisitor::TransformUpdateVisitor( TransformStrategy* s ) : _strategy(s) {}

TransformUpdateVisitor::~TransformUpdateVisitor() { delete _strategy; }

void TransformUpdateVisitor::VisitTransform( Transform* node ) 
{ 
   _strategy->Apply( node ); 
}
