#include "Transform.hpp"

/** \brief Transform Node is initialized with a Name and the identity matrix
 * \param Name of the Node
 */
Transform::Transform(const string& Name) : CompositeNode(Name) { 
	m3dLoadIdentity44( _matrix );
}

/** \brief Transform Node is initialized with a name and a initial transformation matrix
 * \param Name of the Node
 * \param m to use as initial transformation
 */
Transform::Transform(const string& Name, const M3DMatrix44f& m) : CompositeNode(Name) { 
	m3dCopyMatrix44(_matrix, m);
}

/** \brief Destructor. Empty */
Transform::~Transform() { 
	DLOG(INFO) << "~Transform" << endl;
}

/** \brief Set the Transformation Matrix to apply.
 * \param m to use as initial transformation */
void Transform::SetMatrix(const M3DMatrix44f m) { 
	m3dCopyMatrix44( _matrix, m );
}

/** \brief Just calls VisitTransform on the Visitor
 * \param Visitor who is visiting us */
void Transform::Accept( NodeVisitor* Visitor ) 
{ 
	Visitor->VisitTransform( this ); 
}


void Transform::GetMatrix( M3DMatrix44f m ) const { 
	m3dCopyMatrix44( m, _matrix );
}

const M3DMatrix44f& Transform::GetMatrix() const {
	return _matrix;
}

void Transform::Reset() {
	m3dLoadIdentity44( _matrix );
}

void Transform::Translate( float x, float y, float z ) 
{
	_matrix[12] = _matrix[12] + x;
	_matrix[13] = _matrix[13] + y;
	_matrix[14] = _matrix[14] + z;
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
