#pragma once
#include "TransformStrategy.hpp"

class ScaleTransformStrategy : public TransformStrategy {
public:
   ScaleTransformStrategy( float x, float y, float z );
   void transformation();
   
private:
   float _x, _y, _z;
};
