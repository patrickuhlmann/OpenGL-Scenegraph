#pragma once

#include "CompositeNode.hpp"

/**
 * Represents a light in a scene.
 */
class Light : public CompositeNode {
public:
  Light();
  Light( const M3DVector3f, const M3DVector3f, Node* );
  ~Light() {};

  void Accept( NodeVisitor* );

  void SetDirection( const M3DVector3f );
  void SetPostition( const M3DVector3f );

  void SetDiffuse ( const M3DVector4f );
  void SetAmbient ( const M3DVector4f );
  void SetSpecular( const M3DVector4f );

  void GetPosition ( const M3DVector3f ) const;
  void GetDirection( const M3DVector3f ) const;

private:
  GLFrame _frame; 
  M3DVector4f _ambient; // RGBA
  M3DVector4f _diffuse;
  M3DVector4f _specular;
  
  // initialize light component vectors
  void Init();
};
