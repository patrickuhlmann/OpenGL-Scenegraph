#pragma once
#include "TransformStrategy.hpp"

class TranslateTransformStrategy : public TransformStrategy {
public:
   TranslateTransformStrategy( float x, float y, float z );
   void transformation();

private:
   float _x, _y, _z;
};
