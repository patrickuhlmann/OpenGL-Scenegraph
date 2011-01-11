#pragma once
#include "Node.hpp"
#include "Transform.hpp"
#include "../Include/math3d.h"

class TransformStrategy {
public:
  virtual ~TransformStrategy(){};
   /**
    * Perform transformation on a node.
    *
    * @see Node.hpp
    * @param pointer to Node
    */
   void Apply( Transform* );

/**
 * Virtual function that can be overridden in subclasses to 
 * provide custom behaviour.
 * The default behaviour means that the transformation multiplication
 * will be done with the identity matrix.
 */
 virtual void transformation() = 0;
   
protected:
   TransformStrategy();
   M3DMatrix44f _transMatrix;
  
};
