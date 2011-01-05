#include "Material.hpp"

/** Creates a material which has only a AmbientLight and a name. There is no Diffuse or Specular light. The Alpha Value of the object is set to 1 (visible)
*	\param AmbientLight float array containing three elements for red, green and blue component of the light
*	\param Name of the Material
*/
Material::Material(const string& Name, const M3DVector3f& AmbientLight) {
	m3dCopyVector3(_ambient, AmbientLight);
	_transparency = 1;
	_useDiffuse = false;
	_useSpecular = false;
	_name = Name;
}

/** \brief Copy constructor to copy the properties of another Material. These properties are completly independent of the original 
*
* \param Material m to copy the properties from
*/
Material::Material( const Material& m ) { Copy( m ); }

/** \brief Just copies all properties. These properties are completly independent of the original 
*
* \param Material m to assign to our class
*/
void Material::operator= ( const Material& m ) { Copy( m ); }

/** \brief Helper Method to copy a material. It just makes a copy of all properties 
*
* \param Material other to copy the properties from
*/
void Material::Copy( const Material& other )
{
  m3dCopyVector3( _ambient, other._ambient );
  m3dCopyVector3( _diffuse, other._diffuse );
  m3dCopyVector3( _specular, other._specular );
  _shine = other._shine;
  _name = other._name;
  _transparency = other._transparency;
  _useDiffuse = other._useDiffuse;
  _useSpecular = other._useSpecular;
}

/** \brief Sets the Ambient Light of the Material (Ambient is the Light which is always present. No matter how far away or in which direction the viewer is.
*
* \param M3dVector3f AmbientLight float array containing three elements for red, green and blue component of the light
*/
void Material::SetAmbient(const M3DVector3f& AmbientLight )
{
	m3dCopyVector3(_ambient, AmbientLight);
}

/** \brief Sets the Ambient Light of the Material (Ambient is the Light which is always present. No matter how far away or in which direction the viewer is.
*
* \param r for the red component of the light
* \param g for the green component of the light
* \param b for the blue component of the light
*/
void Material::SetAmbient(GLfloat r, GLfloat g, GLfloat b) {
	m3dLoadVector3(_ambient, r, g, b);
}

/** \brief Sets the Diffuse Light of the Material (Diffuse is the light which is dependent of the viewing direction of the user
*
* \param M3dVector3f DiffuseLight float array containing three elements for red, green and blue component of the light
*/
void Material::SetDiffuse(const M3DVector3f& DiffuseLight)
{
	m3dCopyVector3(_diffuse, DiffuseLight);
	_useDiffuse = true;
}

/** \brief Sets the Diffuse Light of the Material (Diffuse is the light which is dependent of the viewing direction of the user
*
* \param r for the red component of the light
* \param g for the green component of the light
* \param b for the blue component of the light
*/
void Material::SetDiffuse(GLfloat r, GLfloat g, GLfloat b) {
	m3dLoadVector3(_diffuse, r, g, b);
}

/** \brief Removes the Diffuse light. So this material has no diffuse light */
void Material::RemoveDiffuse() {
	_useDiffuse = false;
}

/** \brief Sets the Specular Light of the Material (Specular is the light wich is dependent of the viewing direction and creates a bright spot on the object)
*
*	\param SpecularLight float array containing three elements for red, green and blue component of the light
*	\param s shininess of the color (Shininess is a value from 0 (not bright) to 1000 (very bright) to define how bright the Specular Light will be)
*/
void Material::SetSpecular(const M3DVector3f& SpecularLight, int s)
{
	m3dCopyVector3(_specular, SpecularLight);
	_shine = s;
	_useSpecular = true;
}

/** \brief Sets the Specular Light of the Material (Specular is the light wich is dependent of the viewing direction and creates a bright spot on the object)
*
* \param r for the red component of the light
* \param g for the green component of the light
* \param b for the blue component of the light
*	\param s shininess of the color (Shininess is a value from 0 (not bright) to 1000 (very bright) to define how bright the Specular Light will be)
*/
void Material::SetSpecular(GLfloat r, GLfloat g, GLfloat b, int s) {
	m3dLoadVector3(_specular, r, g, b);
	_shine = s;
	_useSpecular = true;
}

/** \brief Removes the Specular Light from this material */
void Material::RemoveSpecular() {
	_useSpecular = false;
}

/** \brief Sets the Alpha value of the object
*
* \param GLflaot a 0 is invisible, 1 is solid visible, values between are partly visible. The background can be seen through
*/
void Material::SetTransparency( GLfloat a ) { 
	_transparency = a;
}

/** \brief Get the name of this material */
const string& Material::GetName() const {
	return _name;
}

/** \brief Check if the Diffuse Light is enabled for this material
* \return true if enabled, false otherwise
*/
bool Material::IsDiffuseLightEnabled() const {
	return _useDiffuse;
}

/** \brief Check if the Specular Light is enabled for this material
* \return true if enabled, false otherwise
*/
bool Material::IsSpecularLightEnabled() const {
	return _useSpecular;
}

/** \brief Return the Diffuse light of this material */
const M3DVector3f& Material::GetDiffuseLight() const {
	return _diffuse;
}

/** \brief Return the Specular Light of this material */
const M3DVector3f& Material::GetSpecularLight() const {
	return _specular;
}

/** \brief Return the Ambient Light of this Material */
const M3DVector3f& Material::GetAmbientLight() const {
	return _ambient;
}

/** \brief Return the Shininess of the Specular Light */
int Material::GetShininess() const {
	return _shine;
}
