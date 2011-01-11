#pragma once

#include "../Include/math3d.h"
#include <string>
#include "../Base/Datatypes.h"
#include <set>

#ifdef MEMORY_CHECK_ACTIVE
	#include "../../Libs/nvwa-0.8.2/debug_new.h"
#endif

using namespace std;

class Material {
public:
  Material(const string& Name, const Vector3& AmbientLight);
  Material(const string& Name, const Vector3& AmbientLight, const Vector3& DiffuseLight);
  Material( const Material& );
  Material( const Material* );
  virtual ~Material() { };
  
  void operator= ( const Material& );
  void SetAmbient(const Vector3& AmbientLight );
  void SetAmbient(float r, float g, float b);
  void SetDiffuse(const Vector3& DiffuseLight );
  void SetDiffuse(float r, float g, float b);
  void SetSpecular(const Vector3& SpecularLight, int s);
  void SetSpecular(float r, float g, float b, int s);
  void RemoveDiffuse();
  void RemoveSpecular();
  void SetTransparency (float);

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
  float     _transparency;
  /** \brief If true it indicates, that the material has a diffuse light, otherwise it's false */
  bool		  _useDiffuse;
  /** \brief If true it indicates, that the material has a specular light, otherwise it's false */
  bool		  _useSpecular;

friend class MeshLoaderObj;
};
