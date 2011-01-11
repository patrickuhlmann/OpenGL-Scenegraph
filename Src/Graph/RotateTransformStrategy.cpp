#include "RotateTransformStrategy.hpp"

RotateTransformStrategy::RotateTransformStrategy( float angle, float x, float y, float z ) :
   _angle(angle), _x(x), _y(y), _z(z)
{}

void RotateTransformStrategy::transformation() 
{
   m3dRotationMatrix44( _transMatrix, _angle, _x, _y, _z ); 
}
