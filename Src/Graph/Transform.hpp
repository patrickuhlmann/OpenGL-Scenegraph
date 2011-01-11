#pragma once

#include <string>
#include "../Include/math3d.h"
#include "CompositeNode.hpp"

using namespace std;

class Transform : public CompositeNode {
public:
	Transform(const string& Name);
	Transform(const M3DMatrix44f& m);
	Transform();

   virtual ~Transform();

  void SetMatrix( M3DMatrix44f m);

  void GetMatrix( M3DMatrix44f m ) const;
  const  M3DMatrix44f& GetMatrix() const;

	void Reset();
  
  // transformations of matrix
  void Translate( float x, float y, float z );
  void Rotate( float angle, float x, float y, float z );
  void Scale( float xScale, float yScale, float zScale );

  virtual void Accept( NodeVisitor* );
  
private:
   M3DMatrix44f _matrix;
};
