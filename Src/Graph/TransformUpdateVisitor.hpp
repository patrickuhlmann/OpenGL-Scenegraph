#pragma once
#include "UpdateVisitor.hpp"
#include "TransformStrategy.hpp"

class TransformUpdateVisitor : public UpdateVisitor {
public:
   // TransformUpdateVisitor();
   TransformUpdateVisitor( const TransformStrategy& );
   
   /**
    * Default implementation of Traverse().
    * TransformUpdaters should not traverse a node.
    */
   void Traverse( CompositeNode* ) {};

   /** 
    * Perform a transformation on the Node's matrix.
    */
   void VisitTransform( Node* );

private:
   TransformStrategy _strategy;

};
