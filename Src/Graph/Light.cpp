#include "Light.hpp"

/** 
* \brief Create a default light object.
* The light will be positioned at the origin, pointing down -z axis
* having the y-axis as the up vector. The light has a white ambient
* light, no diffuse light and no specular light
*/
Light::Light() : CompositeNode() { 
	Init();
};

/** 
 *\brief Create a named default light object.
* The light will be positioned at the origin, pointing down -z axis
* having the y-axis as the up vector. The light has a white ambient
* light, no diffuse light and no specular light
*
* \param Name for the Node
*/
Light::Light(string Name) : CompositeNode(Name) {
	Init();
};

/** 
* \brief Create a light and initialize the position and direction of it
* The light has a white ambient
* light, no diffuse light and no specular light
*
* @param pos from where the light shines
* @param dir in which the light shines
*/
Light::Light( const M3DVector3f pos, const M3DVector3f dir) : CompositeNode() 
{
  _frame.SetOrigin( pos );
  _frame.SetForwardVector( dir );
  Init();
}

/** \brief initialize light component vectors. Ambient is white, all the others will be black */
void Light::Init() 
{
  m3dLoadVector4( _diffuse,  0.0f, 0.0f, 0.0f, 0.0f );
  m3dLoadVector4( _ambient,  1.0f, 1.0f, 1.0f, 1.0f );
  m3dLoadVector4( _specular, 0.0f, 0.0f, 0.0f, 0.0f );
}

/** \brief Accept a visitor. It calls VisitLight on it's Visitor
 *
 * \param visitor who visits us
 */
void Light::Accept( NodeVisitor* visitor ) 
{ 
   DLOG(INFO) << "Light accepted visitor\n";
   visitor->VisitLight( this ); 
}

/**
* \brief Set the direction of the light.
* @param dir direction to set (XYZ)
*/
void Light::SetDirection( const M3DVector3f dir ) {
	_frame.SetForwardVector( dir );
}

/**
* \brief Set the position/origin of the light.
* @param pos to set (XYZ)
*/
void Light::SetPostition( const M3DVector3f pos ) {
	_frame.SetOrigin( pos );
}

/**
* \brief Set the ambient light component.
* @param v  RGBA
*/
void Light::SetAmbient ( const M3DVector4f v ) { 
	m3dCopyVector4( _ambient, v );
}

/**
* \brief Set the diffuse light component.
* @param v  RGBA
*/
void Light::SetDiffuse ( const M3DVector4f v ) { 
	m3dCopyVector4( _diffuse, v );
}

/**
* \brief Set the specular light component.
* @param v  RGBA
*/
void Light::SetSpecular( const M3DVector4f v ) {
	m3dCopyVector4( _specular, v );
}

/**
* \brief Get the lights position/origin.
* @param pos a vector to assign the position to.
*/
void Light::GetPosition( M3DVector3f pos ) const {
	_frame.GetOrigin( pos );
}

/**
* \brief Get the lights direction.
* @param dir a vector to assign the direction to.
*/
void Light::GetDirection( M3DVector3f dir ) const {
	_frame.GetForwardVector( dir );
}

/**
* \brief Get the light's ambient component.
* @param v a vector to assign the component to.
*/
void Light::GetAmbient ( M3DVector4f v ) const {
	m3dCopyVector4( v, _ambient );
} 

/**
* \brief Get the light's diffuse component.
* @param v a vector to assign the component to.
*/
void Light::GetDiffuse ( M3DVector4f v ) const {
	m3dCopyVector4( v, _diffuse );
}

/**
* \brief Get the light's specular component.
* @param v a vector to assign the component to.
*/
void Light::GetSpecular( M3DVector4f v ) const { m3dCopyVector4( v, _specular ); }

