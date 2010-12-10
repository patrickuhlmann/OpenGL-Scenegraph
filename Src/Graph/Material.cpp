#include "Material.hpp"

Material::Material( const Material& ) { Copy( other ); }

void Material::operator= ( const Material& ) { Copy( other ); }

void Material::Copy( const Material& other )
{
  m3dCopyVector4( _ambient, other._ambient );
  m3dCopyVector4( _diffuse, other._diffuse );
  m3dCopyVector4( _specular, other._specular );
  _shine = other._shine;
}

void Material::SetAmbient( GLfloat r, GLfloat b, GLfloat g, GLfloat a )
{ m3dLoadVector4( _ambient, r, g, b, a ); }

void Material::SetDiffuse( GLfloat r, GLfloat g, GLfloat b, GLfloat a )
{ m3dLoadVector4( _diffuse, r, g, b, a ); }

void Material::SetSpecular( GLfloat r, GLfloat g, GLfloat b, GLfloat a )
{ m3dLoadVector( _specular, r, g, b, a ); }

void Material::SetShine( GLchar s ) { _shine = s; }
