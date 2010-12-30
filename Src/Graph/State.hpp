#pragma once

#include <set>
#include "../Include/GL/glew.h"
#include "Material.hpp"

using namespace std;

typedef set< GLenum > StateVariableSet;
typedef StateVariableSet::iterator StateVariableIterator;

/**
 * A class for setting OpenGL state.
 */
class State {
public:
  State();

  /** Copy constructor */
  State( const State& );

  /** Copy assignment */
  void operator= ( const State& );

  /** Apply a state */
  void Apply();

  /** Merge this state with another */
  void Merge( const State& );

  /** Enable a state variable */
  void Enable( GLenum );

  /** Disable a state variable */
  void Disable( GLenum );

  /** Set new material to OpenGL */
  void SetMaterial( const Material& );

  StateVariableIterator GetStateVariableIterator();

  StateVariableIterator GetStateEnableIterator();
  StateVariableIterator GetStateEnableIteratorEnd();

  StateVariableIterator GetStateDisableIterator();
  StateVariableIterator GetStateDisableIteratorEnd();

private:
  StateVariableSet _enables; 
  StateVariableSet _disables;
  Material _material;
  //  Texture _texture;
  
};
