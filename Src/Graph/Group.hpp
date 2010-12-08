#pragma once

class Group : public CompositeNode {
public:
   Group( Node* parent ) : CompositeNode( parent ) {};
   void Accept( NodeVisitor* visitor ) { visitor->VisitGroup( this ); };
};
