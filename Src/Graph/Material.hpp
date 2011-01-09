#pragma once

#include "../Include/math3d.h"
#include "../Include/GL/glew.h"
#include <string>
#include "../Base/Datatypes.h"

using namespace std;

class Material {
public:
  Material(const string& Name, const Vector3& AmbientLight);
  Material( const Material& );
  Material( const Material* );
  ~Material() { };
  
  void operator= ( const Material& );
  void SetAmbient(const Vector3& AmbientLight );
  void SetAmbient(GLfloat r, GLfloat g, GLfloat b);
  void SetDiffuse(const Vector3& DiffuseLight );
  void SetDiffuse(GLfloat r, GLfloat g, GLfloat b);
  void SetSpecular(const Vector3& SpecularLight, int s);
  void SetSpecular(GLfloat r, GLfloat g, GLfloat b, int s);
  void RemoveDiffuse();
  void RemoveSpecular();
  void SetTransparency (GLfloat);

  const string& GetName() const;
  bool IsDiffuseLightEnabled() const;
  bool IsSpecularLightEnabled() const;
  int GetShininess() const;
  const Vector3& GetDiffuseLight() const;
  const Vector3& GetSpecularLight() const;
  const Vector3& GetAmbientLight() const;

private:
  void Copy( const Material& );
  void Copy( const Material* );

  /** \brief Store the r, g and b components of the Ambient light */
  Vector3 _ambient;
  /** \brief Store the r, g and b components of the Diffuse light */
  Vector3 _diffuse;
  /** \brief Store the r, g and b components of the Specular light */
  Vector3 _specular;
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
