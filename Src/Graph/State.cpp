#include "State.hpp"

State::State() {}

State::~State() {
	if (_material)
		delete _material;
}

State::State( const State& other ) { Merge( other ); }

void State::operator= ( const State& other )
{
  _disables.clear();
  _enables.clear();
  Merge( other );
}

void State::Apply()
{
  StateVariableIterator disableIt, disableEnd, enableIt, enableEnd;
  disableIt  = _disables.begin();
  disableEnd = _disables.end();
  enableIt   = _enables.begin();
  enableEnd  = _enables.end();

  while ( enableIt != enableEnd ) {
    glEnable( *enableIt );
    ++enableIt;
  }

  while ( disableIt != disableEnd ) {
    glDisable( *disableIt );
    ++disableIt;
  }
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

void State::SetMaterial( const Material& m ) { 
  if (_material)
    delete _material;

   _material = new Material(m);
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

StateVariableIterator State::GetStateVariableIterator()
{ return _enables.begin(); }

StateVariableIterator State::GetStateEnableIteratorEnd()
{ return _enables.end(); }

StateVariableIterator State::GetStateDisableIterator()
{ return _disables.begin(); }

StateVariableIterator State::GetStateDisableIteratorEnd()
{ return _disables.end(); }
