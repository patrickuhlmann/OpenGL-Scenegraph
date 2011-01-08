#include "UpdateVisitor.hpp"

UpdateVisitor::UpdateVisitor(){}

UpdateVisitor::~UpdateVisitor() {
	if (_material)
		delete _material;
}

void UpdateVisitor::VisitTransform( Transform* t ) 
{

}

void UpdateVisitor::VisitGeometry( Geometry* g )
{
}

void UpdateVisitor::VisitLight( Light* l )
{
}

void UpdateVisitor::VisitGroup( Group* g )
{

}

void UpdateVisitor::VisitCamera( Camera* c )
{

}

void UpdateVisitor::SetTransform( const M3DMatrix44f& t ) 
{ m3dCopyMatrix44( _transform, t ); }

void UpdateVisitor::SetDirection( const M3DVector3f& d ) 
{ m3dCopyVector3( _direction, d ); }

void UpdateVisitor::SetPosition( const M3DVector3f& p )
{ m3dCopyVector3( _position, p ); }

void UpdateVisitor::SetState(State* s ) { _state = s; }

void UpdateVisitor::SetMaterial ( const Material& m ) { 
    if (_material)
		delete _material;

	_material = new Material(m);
}

// TODO: implement
void UpdateVisitor::Traverse( CompositeNode* c ) {

}
