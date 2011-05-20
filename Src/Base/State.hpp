#pragma once

#include <set>
#include "Material.hpp"
#include <glog/logging.h>

#ifdef MEMORY_CHECK_ACTIVE
	#include "../../Libs/nvwa-0.8.2/debug_new.h"
#endif

using namespace std;

typedef set<int> StateVariableSet;
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

	/** \brief function to Apply the States. Needs to be implemeneted by the concrete state like OpenGL or DirectX */
	virtual void Apply() const = 0;
	/** \brief function to Undo the changes from the states. This needs to be done when we are finished traversing the children and want to change to another branch where those states are not active */
	virtual void Undo() const = 0;

	void Enable(int);
	void Disable(int);

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
