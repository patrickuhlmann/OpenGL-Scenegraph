#include "Transform.hpp"

Transform::~Transform() { }

void Transform::SetMatrix( M3DMatrix44f m ) { m3dCopyMatrix44( _matrix, m ); }

void Transform::Accept( NodeVisitor* visitor ) 
{ 
   visitor->VisitTransform( this ); 
}

void Transform::GetMatrix( M3DMatrix44f m ) const { m3dCopyMatrix44( m, _matrix ); }

const M3DMatrix44f& Transform::GetMatrix() const { return _matrix; }

void Transform::Reset() {
	m3dLoadIdentity44( _matrix );
}

void Transform::Translate( float x, float y, float z ) 
{
	M3DMatrix44f _transmatrix;
	m3dTranslationMatrix44( _transmatrix, x, y, z );
	M3DMatrix44f _source;
	m3dCopyMatrix44(_source, _matrix);

	m3dMatrixMultiply44(_matrix, _source, _transmatrix);
}

void Transform::Rotate( float angle, float x, float y, float z ) 
{
	M3DMatrix44f _rotmatrix;
	m3dRotationMatrix44( _rotmatrix, angle, x, y, z );
	M3DMatrix44f _source;
	m3dCopyMatrix44(_source, _matrix);

	m3dMatrixMultiply44(_matrix, _source, _rotmatrix);
}

void Transform::Scale( float xScale, float yScale, float zScale ) 
{
	M3DMatrix44f _scmatrix;
	m3dScaleMatrix44( _scmatrix, xScale, yScale, zScale );
	M3DMatrix44f _source;
	m3dCopyMatrix44(_source, _matrix);

	m3dMatrixMultiply44(_matrix, _source, _scmatrix);
}
