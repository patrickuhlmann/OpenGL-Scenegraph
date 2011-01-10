#pragma once
#include "TransformStrategy.hpp"

class RotateTransformStrategy : public TransformStrategy {
public:
   RotateTransformStrategy( float, float, float, float );

   // Default copy constructor is sufficient

   /**
    * Multiply rotation on matrix in given node.
    *
    * @see Node
    * @param pointer to a Node
    */
   void transformation();

private:
   float _angle, _x, _y, _z;
};
