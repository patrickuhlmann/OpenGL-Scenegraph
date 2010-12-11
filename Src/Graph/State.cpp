#include "State.hpp"

State::State() {}

State::State( const State& other ) { Merge( other ); }

void State::operator= ( const State& other )
{
  _disables.clear();
  _enables.clear();
  Merge( other );
}

void State::Enable ( GLenum val ) 
{
  _disables.erase( val );
  _enables.insert ( val ); 
}

void State::Disable( GLenum val ) 
{ 
  _enables.erase( val );
  _disables.insert( val );
 }

void State::Merge( const State& state )
{
  StateVariableIterator enableIterator, enableEnd, disableIterator, disableEnd;
  enableIterator  = state._enables.begin();
  enableEnd       = state._enables.end();
  disableIterator = state._disables.begin();
  disableEnd       = state._disables.end();

  while ( enableIterator != enableEnd )
    _enables.insert( (*enableIterator) );

  while ( disableIterator != disableEnd )
    _disables.insert( (*disableIterator) );
 
  _material = state._material;
}
