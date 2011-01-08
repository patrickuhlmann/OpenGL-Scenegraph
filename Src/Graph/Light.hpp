#pragma once

#include "CompositeNode.hpp"
#include "../Include/GLFrame.h"
#include <string>

using namespace std;

/**
 * \brief Light represents a light node in the scene. This light has basic properties like a Direction and Position. It can use Ambient, Diffuse and Specular Light. Furthermore it can be Visited
 * @author Steve Eriksson
 */
class Light : public CompositeNode {
public:
  Light();
  Light(string Name);
  Light( const M3DVector3f, const M3DVector3f);

  void Accept( NodeVisitor* );

  void SetDirection( const M3DVector3f );
  void SetPostition( const M3DVector3f );
  void SetDiffuse( const M3DVector4f );
  void SetAmbient( const M3DVector4f );
  void SetSpecular( const M3DVector4f );

  void GetPosition( M3DVector3f ) const;
  void GetDirection( M3DVector3f ) const;
  void GetDiffuse( M3DVector4f ) const;
  void GetAmbient( M3DVector4f ) const;
  void GetSpecular( M3DVector4f ) const;

private:
	/** \brief Handles position, direction and movement of the light. */
	GLFrame     _frame;   
	/** \brief Ambient component. RGBA.  */ 
	M3DVector4f _ambient;
	/** \brief Diffuse component. RGBA.  */
	M3DVector4f _diffuse;
	/** \brief Specular component. RGBA. */
	M3DVector4f _specular;
	
  
  void Init();
};
