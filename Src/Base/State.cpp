#include "State.hpp"

/** \brief Default Constructor does nothing */
State::State() : _material(0), _enables(0), _disables(0) {
}

/** \brief Deletes the Material, Enable list and disable list */
State::~State() {
	DLOG(INFO) << "~State" << endl;
	delete _material;
	delete _enables;
	delete _disables;
}

/** \brief Copy all the Enables and Disables to this state
 * \param other the state to copy from
 */
State::State(const State& other) {
	// same effect as copy as our state is empty
	Merge(other);
}

/** \brief Copy all the Enables and Disables to this State 
 * \param other the state to copy from
 */
void State::operator= (const State& other)
{
	if (_disables)
		_disables->clear();

	if (_enables)
		_enables->clear();

	Merge( other );
}

/** \brief Enable a State. If it is already disabled it will be deleted from the disables list. In every case it will be added to the enables list. It will only save it to a list. To really apply you need to call apply.
 * \param val of the state to enable */
void State::Enable ( int val ) 
{
	if (_disables)
		_disables->erase( val );

	if (!_enables)
		_enables = new StateVariableSet();

	_enables->insert ( val ); 
}

/** \brief Disable a State. If it is already enabled it will be deleted from the enable list. In every case it will be added to the disable list. It will only save it to a list. To really apply it you need to call apply.
  * \param val of the state to disable */
void State::Disable( int val ) 
{ 
	if (_enables)
		_enables->erase( val );

	if (!_disables)
		_disables = new StateVariableSet();

	_disables->insert( val );
}

/** \brief Set a Material for this State. We take ownership of the Material and will also delete it at the end!
  * \param m for this state
  */
void State::SetMaterial( const Material& m ) { 
	delete _material;
	_material = new Material(m);
}

/** \brief Merge this state with another one. We take all enables and disables and put them in our lists. If there is one disabled and one enabled (the same number) the last one wins which meanst the state in the argument state overwrites the old one
  * \param state which we merge with ourselves
  */
void State::Merge( const State& state )
{
	if (state._enables) {
		for (StateVariableIterator EnableIt = state._enables->begin(); EnableIt != state._enables->end(); ++EnableIt) {
			this->Enable(*EnableIt);
		}
	}

	if (state._disables) {
		for (StateVariableIterator DisableIt = _disables->begin(); DisableIt != _disables->end(); ++DisableIt) {
			this->Disable(*DisableIt);
		}
	}

	if (state._material) {
		if (_material)
			delete _material;

		_material = new Material(*(state._material));
	}
}
