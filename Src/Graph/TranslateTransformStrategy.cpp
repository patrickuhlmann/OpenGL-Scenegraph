#include "TranslateTransformStrategy.hpp"

TranslateTransformStrategy::TranslateTransformStrategy( float x, float y, float z ) : _x(x), _y(y), _z(z) {}

void TranslateTransformStrategy::transformation() { m3dTranslationMatrix44( _transMatrix, _x, _y, _z ); }
