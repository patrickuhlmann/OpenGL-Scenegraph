#pragma once

#include "CompositeNode.hpp"
#include "State.hpp"
#include <string>
#include "../Base/Datatypes.h"

using namespace std;

/**
 * \brief Light represents a light node in the scene. This light has basic properties like a Direction and Position. It can use Ambient, Diffuse and Specular Light. Furthermore it can be Visited. It has a Changed flag which will be set from the class whenever we change one of the properties.
 * @author Steve Eriksson
 */
class Light : public CompositeNode {
public:
  Light(string Name = "");
  Light(const Vector4 pos);
  ~Light();

  void Accept( NodeVisitor* );

  void SetPosition(const Vector4&);
  void SetDiffuse(const Vector4&);
  void SetAmbient(const Vector4&);
  void SetSpecular(const Vector4&);

  const Vector4& GetPosition() const;
  const Vector4& GetDiffuse() const;
  const Vector4& GetAmbient() const;
  const Vector4& GetSpecular() const;

  bool IsChanged() const;
  bool SetChanged(bool NewValue);

  State* GetState() const;
  void SetState(State* NewState);

  int GetLightNumber() const;
  void SetLightNumber(int NewNumber);

private:
	/** \brief Represents the Position of the Light */
	Vector4 _position;
	/** \brief Ambient component. RGBA.  */ 
	Vector4 _ambient;
	/** \brief Diffuse component. RGBA.  */
	Vector4 _diffuse;
	/** \brief Specular component. RGBA. */
	Vector4 _specular;
	/** \brief Indicates if there was a change */
	bool Changed;
	/** \brief Represents the state of the object */
	State* _state;
	/** \brief Represents the Index of the Light for the Graphics Framework */
	int LightNumber;

	void Init();
};
