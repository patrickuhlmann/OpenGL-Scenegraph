#include "Light.hpp"

Light::Light() { Init(); }; // parent is NULL, forward is -Z, up is Y and position is origin

Light::Light( const M3DVector3f pos, const M3DVector3f dir, Node* parent) : CompositeNode( parent ) 
{
  // UpVector is Y axis by default
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

void Light::Accept( NodeVisitor* visitor ) { visitor->VisitLight( this ); }

void Light::SetDirection( const M3DVector3f dir ) { _frame.SetForwardVector( dir ); }

void Light::SetPostition( const M3DVector3f pos ) { _frame.SetOrigin( pos ); }

void Light::SetDiffuse( const M3DVector4f v ) { m3dCopyVector4( _diffuse, v ); }

void Light::SetAmbient( const M3DVector4f v ) { m3dCopyVector4( _ambient, v ); }

void Light::SetSpecular( const M3DVector4f v) { m3dCopyVector4( _specular, v ); }


void Light::GetPosition( const M3DVector3f pos ) const { _frame.setOrigin( pos ); }

void Light::GetDirection( const M3DVector3f dir ) const { _frame.SetForwardVector( dir ); }

