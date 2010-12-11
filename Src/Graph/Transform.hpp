#pragma once

#include "../Include/math3d.h"
#include "CompositeNode.hpp"

class Transform : public CompositeNode {
public:
   Transform( const M3DMatrix44f& m ) { m3dCopyMatrix44(_matrix, m); };
   Transform( const M3DMatrix44f& m, Node* parent ) : CompositeNode( parent ) { m3dCopyMatrix44(_matrix, m); };

   ~Transform();

  void SetMatrix( M3DMatrix44f m);

  void GetMatrix( M3DMatrix44f m ) const;
  const  M3DMatrix44f& GetMatrix() const;
  
  // transformations of matrix
  void Translate( float x, float y, float z );
  void Rotate( float angle, float x, float y, float z );
  void Scale( float xScale, float yScale, float zScale );

  virtual void Accept( NodeVisitor* );
  
private:
   M3DMatrix44f _matrix;
};
