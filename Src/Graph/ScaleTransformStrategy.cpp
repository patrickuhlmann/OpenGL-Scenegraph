#include "ScaleTransformStrategy.hpp"

ScaleTransformStrategy::ScaleTransformStrategy( float x, float y, float z ) : _x(x), _y(y), _z(z) {}

void ScaleTransformStrategy::transformation() { m3dScaleMatrix44( _transMatrix, _x, _y, _z ); }
