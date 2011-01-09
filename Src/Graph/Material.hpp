#pragma once

#include "../Include/math3d.h"
#include "../Include/GL/glew.h"
#include <string>

using namespace std;

class Material {
public:
  Material(const string& Name, const M3DVector3f& AmbientLight);
  Material( const Material& );
  Material( const Material* );
  ~Material() { };
  
  void operator= ( const Material& );
  void SetAmbient(const M3DVector3f& AmbientLight );
  void SetAmbient(GLfloat r, GLfloat g, GLfloat b);
  void SetDiffuse(const M3DVector3f& DiffuseLight );
  void SetDiffuse(GLfloat r, GLfloat g, GLfloat b);
  void SetSpecular(const M3DVector3f& SpecularLight, int s);
  void SetSpecular(GLfloat r, GLfloat g, GLfloat b, int s);
  void RemoveDiffuse();
  void RemoveSpecular();
  void SetTransparency (GLfloat);

  const string& GetName() const;
  bool IsDiffuseLightEnabled() const;
  bool IsSpecularLightEnabled() const;
  int GetShininess() const;
  const M3DVector3f& GetDiffuseLight() const;
  const M3DVector3f& GetSpecularLight() const;
  const M3DVector3f& GetAmbientLight() const;

private:
  void Copy( const Material& );
  void Copy( const Material* );

  /** \brief Store the r, g and b components of the Ambient light */
  M3DVector3f _ambient;
  /** \brief Store the r, g and b components of the Diffuse light */
  M3DVector3f _diffuse;
  /** \brief Store the r, g and b components of the Specular light */
  M3DVector3f _specular;
  /** \brief Store how strong the specular hightlight is shining */
  int      _shine;
  /** \brief Store a name for the material */
  string      _name;
  /** \brief Store the alpha value for the material */
  GLfloat     _transparency;
  /** \brief If true it indicates, that the material has a diffuse light, otherwise it's false */
  bool		  _useDiffuse;
  /** \brief If true it indicates, that the material has a specular light, otherwise it's false */
  bool		  _useSpecular;

friend class MeshLoaderObj;
};
