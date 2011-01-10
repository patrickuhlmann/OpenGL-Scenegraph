#include "TransformUpdateVisitor.hpp"

TransformUpdateVisitor::TransformUpdateVisitor( const TransformStrategy& s ) : _strategy(s) {}

void TransformUpdateVisitor::VisitTransform( Node* node ) { _strategy( node ); }
