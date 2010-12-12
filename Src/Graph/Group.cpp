#include "Group.hpp"

void Group::accept( NodeVisitor* visitor ) { visitor->visit_group( this ); }

void Group::SetState( const State& s ) { _state = s; }
