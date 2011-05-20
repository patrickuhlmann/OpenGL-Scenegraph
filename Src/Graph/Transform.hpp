#pragma once

#include <string>
#include "../Include/math3d.h"
#include "CompositeNode.hpp"

using namespace std;

/** \brief This node supports some transformation operations such as Translate, Rotate and Scale. The operations are adding up (two times translation (1, 0, 0) is the same as once (2, 0, 0) and apply for all children. However it is possible to reset the transformations to nothing */
class Transform : public CompositeNode {
public:
	Transform(const string& Name);
	Transform(const string& Name, const M3DMatrix44f& m);

	virtual ~Transform();

	void SetMatrix(const M3DMatrix44f m);
	void GetMatrix( M3DMatrix44f m ) const;
	const  M3DMatrix44f& GetMatrix() const;

	void Reset();
  
	void Translate( float x, float y, float z );
	void Rotate( float angle, float x, float y, float z );
	void Scale( float xScale, float yScale, float zScale );

	virtual void Accept( NodeVisitor* );
  
private:
	/** \brief stores the cummulation of all transoformations */
	M3DMatrix44f _matrix;
};
