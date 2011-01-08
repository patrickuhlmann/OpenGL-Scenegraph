#include "Group.hpp"

Group::Group( const std::string& name ) : CompositeNode( name ) {}
void Group::Accept( NodeVisitor* visitor )
{
   visitor->VisitGroup( this );
}
