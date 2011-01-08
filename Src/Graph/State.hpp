#pragma once

#include <set>
#include "../Include/GL/glew.h"
#include "Material.hpp"

using namespace std;

typedef set<GLenum> StateVariableSet;
typedef StateVariableSet::iterator StateVariableIterator;

/**
 * Abstract class to Enable and Disable a State of the Rendering. You can add as many Enable/Disables as you want, you can apply them to the actual state and you can Merge this state with another one
 */
class State {
public:
	virtual ~State();
	State();
	State( const State& );

	void operator= ( const State& );

	/** Function to Apply the States. Needs to be implemeneted by the concrete state like OpenGL or DirectX */
	virtual void Apply() = 0;

	void Enable(GLenum);
	void Disable(GLenum);

	void SetMaterial(const Material&);

	void Merge( const State& );

protected:
	/** \brief Holds a Set of all the States to Enable */
	StateVariableSet* _enables; 
	/** \brief Holds a Set of all the States to Disable */
	StateVariableSet* _disables;
	/** \brief Holds the Material for this State */
	Material* _material;
};
