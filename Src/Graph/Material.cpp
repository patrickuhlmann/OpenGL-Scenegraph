#include "Material.hpp"

Material::Material( const Material& m ) { Copy( m ); }

void Material::operator= ( const Material& m ) { Copy( m ); }

void Material::Copy( const Material& other )
{
  m3dCopyVector3( _ambient, other._ambient );
  m3dCopyVector3( _diffuse, other._diffuse );
  m3dCopyVector3( _specular, other._specular );
  _shine = other._shine;
  _name = other._name;
  _transparency = other._transparency;
}

void Material::SetAmbient( GLfloat r, GLfloat b, GLfloat g )
{ m3dLoadVector3( _ambient, r, g, b); }

void Material::SetDiffuse( GLfloat r, GLfloat g, GLfloat b)
{ m3dLoadVector3( _diffuse, r, g, b); }

void Material::SetSpecular( GLfloat r, GLfloat g, GLfloat b )
{ m3dLoadVector3( _specular, r, g, b ); }

void Material::SetShine( GLchar s ) { _shine = s; }

void Material::SetTransparency( GLfloat a ) { _transparency = a; }
