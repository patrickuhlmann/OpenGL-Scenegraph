#include "Light.hpp"

/** 
* \brief Create a light and initialize the position. The light will have no ambient but white diffuse and specular component. It initializes Changed to true
*
* \param Name for the Node
*/
Light::Light(string Name) : CompositeNode(Name) {
	Init();
};

/** 
* \brief Create a light and initialize the position. The light will have no ambient but white diffuse and specular component. It initializes Changed to true
*
* @param pos from where the light shines
*/
Light::Light(const Vector4 pos) : CompositeNode() 
{
	Init();
	_position = Vector4(pos);
	this->Changed = true;
}

/** \brief Free the State */
Light::~Light() {
	DLOG(INFO) << "~Light" << endl;
	delete _state;
}

/** \brief initialize light component vectors. Light from left upper edge. No ambient but white diffuse and specular light */
void Light::Init() 
{
	_position = Vector4(1.0f, 1.0f, 0.0f, 1.0f);
	_ambient = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
	_diffuse = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	_specular = Vector4(1.0f, 1.0f, 1.0f, 1.0f);

	_state = 0;
	LightNumber = 0;
}

/** \brief Accept a visitor. It calls VisitLight on it's Visitor
 *
 * \param visitor who visits us
 */
void Light::Accept( NodeVisitor* visitor ) 
{ 
   visitor->VisitLight(this); 
}

/**
* \brief Set the position/origin of the light.
* @param pos to set (XYZ)
*/
void Light::SetPosition( const Vector4& pos ) {
	_position = Vector4(pos);
	this->Changed = true;
}

/**
* \brief Set the ambient light component.
* @param v  RGBA
*/
void Light::SetAmbient (const Vector4& v) { 
	_ambient = Vector4(v);
	this->Changed = true;
}

/**
* \brief Set the diffuse light component.
* @param v  RGBA
*/
void Light::SetDiffuse (const Vector4& v) {
DLOG(INFO) << "def: " << v.Components.x << ", " << v.Components.y << ", " << v.Components.z << ", " << v.Components.w << endl;

	_diffuse = Vector4(v);
	this->Changed = true;
}

/**
* \brief Set the specular light component.
* @param v  RGBA
*/
void Light::SetSpecular(const Vector4& v) {
	_specular = Vector4(v);
	this->Changed = true;
}

/**
* \brief Get the lights position/origin.
* @param pos a vector to assign the position to.
*/
const Vector4& Light::GetPosition() const {
	return _position;
}

/**
* \brief Get the light's ambient component.
* @param v a vector to assign the component to.
*/
const Vector4& Light::GetAmbient () const {
	return _ambient;
} 

/**
* \brief Get the light's diffuse component.
* @param v a vector to assign the component to.
*/
const Vector4& Light::GetDiffuse () const {
	return _diffuse;
}

/**
* \brief Get the light's specular component.
* @param v a vector to assign the component to.
*/
const Vector4& Light::GetSpecular() const {
	return _specular;
}

/** \brief Return the Changed flag of this class */
bool Light::IsChanged() const {
	return this->Changed;
}

/** \brief Set a new value for the changed flag of this class 
 * \param NewValue to set
 */
bool Light::SetChanged(bool NewValue) {
	this->Changed = NewValue;
}

/** \brief Get a reference to the State of the Light Node
 */
State* Light::GetState() const {
	return _state;
}

/** \brief Set a new State for the Light node. This will remove the old one and we take control of the State. We also delete it at the end
 * \param NewState to set
 */
void Light::SetState(State* NewState) {
	delete _state;
	_state = NewState;
}

/** \brief Get the Light Index */
int Light::GetLightNumber() const {
	return this->LightNumber;
}

/** \brief Set the Light Index
  * \param NewIndex for the Light
  */
void Light::SetLightNumber(int NewNumber) {
	this->LightNumber = NewNumber;
}


