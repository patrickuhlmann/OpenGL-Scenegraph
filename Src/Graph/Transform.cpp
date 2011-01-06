#include "Transform.hpp"

Transform::~Transform() { delete [] _matrix; }

void Transform::SetMatrix( M3DMatrix44f m ) { m3dCopyMatrix44(m, _matrix); }

void Transform::Accept( NodeVisitor* visitor ) 
{ 
   DLOG(INFO) << "Transform accepted visitor\n";
   visitor->VisitTransform( this ); 
}

void Transform::GetMatrix( M3DMatrix44f m ) const { m3dCopyMatrix44(m, _matrix ); }

const M3DMatrix44f& Transform::GetMatrix() const { return _matrix; }

void Transform::Translate( float x, float y, float z ) 
{ m3dTranslationMatrix44( _matrix, x, y, z ); }

void Transform::Rotate( float angle, float x, float y, float z ) 
{ m3dRotationMatrix44( _matrix, angle, x, y, z ); }

void Transform::Scale( float xScale, float yScale, float zScale ) 
{ m3dScaleMatrix44( _matrix, xScale, yScale, zScale ); }
