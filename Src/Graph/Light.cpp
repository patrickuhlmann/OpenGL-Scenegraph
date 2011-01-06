#include "Light.hpp"

Light::Light() { Init(); };

Light::Light( const M3DVector3f pos, const M3DVector3f dir, Node* parent) : CompositeNode() 
{
  _frame.SetOrigin( pos );
  _frame.SetForwardVector( dir );
  Init();
}

void Light::Init() 
{
  m3dLoadVector4( _diffuse,  0.0f, 0.0f, 0.0f, 0.0f );
  m3dLoadVector4( _ambient,  0.0f, 0.0f, 0.0f, 0.0f );
  m3dLoadVector4( _specular, 0.0f, 0.0f, 0.0f, 0.0f );
}

void Light::Accept( NodeVisitor* visitor ) 
{ 
   DLOG(INFO) << "Camera accepted visitor\n";
   visitor->VisitLight( this ); 
}


void Light::SetDirection( const M3DVector3f dir ) { _frame.SetForwardVector( dir ); }
void Light::SetPostition( const M3DVector3f pos ) { _frame.SetOrigin( pos ); }

void Light::SetDiffuse ( const M3DVector4f v ) { m3dCopyVector4( _diffuse, v ); }
void Light::SetAmbient ( const M3DVector4f v ) { m3dCopyVector4( _ambient, v ); }
void Light::SetSpecular( const M3DVector4f v ) { m3dCopyVector4( _specular, v ); }

void Light::GetDiffuse ( M3DVector4f v ) const { m3dCopyVector4( v, _diffuse ); }
void Light::GetAmbient ( M3DVector4f v ) const { m3dCopyVector4( v, _ambient ); } 
void Light::GetSpecular( M3DVector4f v ) const { m3dCopyVector4( v, _specular ); }

void Light::GetPosition( M3DVector3f pos ) const { _frame.GetOrigin( pos ); }

// REMOVE
// GLfloat* Light::GetPosition() const
// {
//   GLfloat* pos = new GLfloat[3];
//   pos[0] = _frame.GetOriginX();
//   pos[1] = _frame.GetOriginY();
//   pos[2] = _frame.GetOriginZ();

//   return pos;
// }

void Light::GetDirection( M3DVector3f dir ) const { _frame.GetForwardVector( dir ); }


