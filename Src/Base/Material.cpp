#include "Material.hpp"

/** Creates a material which has only a AmbientLight and a name. There is no Diffuse or Specular light. The Alpha Value of the object is set to 1 (visible)
*	\param Name of the Material
*	\param AmbientLight float array containing three elements for red, green and blue component of the light
*/
Material::Material(const string& Name, const Vector3& AmbientLight) {
	_ambient = Vector3(AmbientLight);
	_transparency = 1;
	_useDiffuse = false;
	_useSpecular = false;
	_name = Name;
	_shine = 0;
}

/** \brief Copy constructor to copy the properties of another Material. These properties are completly independent of the original 
*
* \param m to copy the properties from
*/
Material::Material( const Material& m ) { Copy( m ); }

Material::Material( const Material* m) {
	Copy(m); 
}

/** \brief Just copies all properties. These properties are completly independent of the original 
*
* \param m to assign to our class
*/
void Material::operator= ( const Material& m ) { Copy( m ); }

/** \brief Helper Method to copy a material. It just makes a copy of all properties 
*
* \param other to copy the properties from
*/
void Material::Copy( const Material& other )
{
	_ambient = Vector3(other._ambient);
	_diffuse = Vector3(other._diffuse);
	_specular = Vector3(other._specular);
	_shine = other._shine;
	_name = string(other._name);
	_transparency = other._transparency;
	_useDiffuse = other._useDiffuse;
	_useSpecular = other._useSpecular;
}

/** \brief Helper Method to copy a material. It just makes a copy of all properties 
*
* \param other to copy the properties from
*/
void Material::Copy( const Material* other )
{
	_ambient = Vector3(other->_ambient);
	_diffuse = Vector3(other->_diffuse);
	_specular = Vector3(other->_specular);
	_shine = other->_shine;
	_name = string(other->_name);
	_transparency = other->_transparency;
	_useDiffuse = other->_useDiffuse;
	_useSpecular = other->_useSpecular;
}

/** \brief Sets the Ambient Light of the Material (Ambient is the Light which is always present. No matter how far away or in which direction the viewer is.
*
* \param AmbientLight float array containing three elements for red, green and blue component of the light
*/
void Material::SetAmbient(const Vector3& AmbientLight )
{
	_ambient = Vector3(AmbientLight);
}

/** \brief Sets the Ambient Light of the Material (Ambient is the Light which is always present. No matter how far away or in which direction the viewer is.
*
* \param r for the red component of the light
* \param g for the green component of the light
* \param b for the blue component of the light
*/
void Material::SetAmbient(float r, float g, float b) {
	_ambient = Vector3(r, g, b);
}

/** \brief Sets the Diffuse Light of the Material (Diffuse is the light which is dependent of the viewing direction of the user
*
* \param DiffuseLight float array containing three elements for red, green and blue component of the light
*/
void Material::SetDiffuse(const Vector3& DiffuseLight)
{
	_diffuse = Vector3(DiffuseLight);
	_useDiffuse = true;
}

/** \brief Sets the Diffuse Light of the Material (Diffuse is the light which is dependent of the viewing direction of the user
*
* \param r for the red component of the light
* \param g for the green component of the light
* \param b for the blue component of the light
*/
void Material::SetDiffuse(float r, float g, float b) {
	_diffuse = Vector3(r, g, b);
	_useDiffuse = true;
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
void Material::SetSpecular(const Vector3& SpecularLight, int s)
{
	_specular = Vector3(SpecularLight);
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
void Material::SetSpecular(float r, float g, float b, int s) {
	_specular = Vector3(r, g, b);
	_shine = s;
	_useSpecular = true;
}

/** \brief Removes the Specular Light from this material */
void Material::RemoveSpecular() {
	_useSpecular = false;
}

/** \brief Sets the Alpha value of the object
*
* \param a 0 is invisible, 1 is solid visible, values between are partly visible. The background can be seen through
*/
void Material::SetTransparency( float a ) { 
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
const Vector3& Material::GetDiffuseLight() const {
	return _diffuse;
}

/** \brief Return the Specular Light of this material */
const Vector3& Material::GetSpecularLight() const {
	return _specular;
}

/** \brief Return the Ambient Light of this Material */
const Vector3& Material::GetAmbientLight() const {
	return _ambient;
}

/** \brief Return the Shininess of the Specular Light */
int Material::GetShininess() const {
	return _shine;
}
