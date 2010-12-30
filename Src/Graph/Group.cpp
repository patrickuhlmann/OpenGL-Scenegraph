#include "Group.hpp"

void Group::Accept( NodeVisitor* visitor ) { visitor->VisitGroup( this ); }

void Group::SetState( const State& s ) { _state = s; }
