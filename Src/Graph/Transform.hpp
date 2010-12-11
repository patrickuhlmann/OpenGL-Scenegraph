#pragma once

#include "CompositeNode.hpp"
#include "../include/math3d.h"

class Transform : public CompositeNode {
public:
   Transform( const M3DMatrix44f& m ) : _matrix(m) {};
   Transform( const M3DMatrix44f& m, Node* parent ) 
      : CompositeNode( parent ), _matrix(m) {};

   ~Transform() {};

  void SetMatrix( const M3Dmatrix44f );
  void GetMatrix( const M3DMatrix44f m ) const;
  const  M3DMatrix44f& GetMatrix() const;
  
  // transformations of matrix
  void Translate( float x, float y, float z );
  void Rotate( float angle, float x, float y, float z );
  void Scale( float xScale, float yScale, float zScale );

  virtual void Accept( NodeVisitor* );
  
private:
   M3DMatrix44f _matrix;
};
