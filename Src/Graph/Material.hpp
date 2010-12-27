#pragma once

#include "../Include/math3d.h"
#include "../Include/GL/glew.h"
#include <string>

using namespace std;

class Material {
public:
  Material() {};
  Material( const Material& );
  
  void operator= ( const Material& );

  /** Set ambient material color. */
  void SetAmbient( GLfloat, GLfloat, GLfloat );

  /** Set diffuse material color. */
  void SetDiffuse( GLfloat, GLfloat, GLfloat );

  /** Set specular material color. */
  void SetSpecular( GLfloat, GLfloat, GLfloat );

  /** 
   * Set the shininess of the material.
   * Values between 0-127 where 0 is shiniest. 
   */
  void SetShine( GLchar );

  void SetTransparency ( GLfloat);

private:
  void Copy( const Material& );

  M3DVector3f _ambient;  /**< Ambient component. RGBA.  */
  M3DVector3f _diffuse;  /**< Diffuse component. RGBA.  */
  M3DVector3f _specular; /**< Specular component. RGBA. */
  GLchar      _shine;    /**< Material shine */
  string      _name;
  GLfloat     _transparency;

friend class MeshLoaderObj;
};
