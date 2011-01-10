#pragma once

#include "CompositeNode.hpp"
#include "../Base/Mesh.hpp"
#include "../Base/State.hpp"
#include <string>

using namespace std;

/**
 * A leaf node representing a graphical object.
 */
class Geometry : public CompositeNode {
public:
	Geometry(Mesh* M, const string& Name = "");
	~Geometry();

  /** Accept a visitor */
  void Accept( NodeVisitor* );

  /** Set the mesh pointer */
  void SetMesh( Mesh* );

  /** Return the mesh pointer */
 const Mesh* GetMesh() const;

  void SetState(State*);

private:
  Mesh* _mesh;  /**< Pointer to a mesh */
  State* _state; /**< State information */
  bool  _dirty; /**< Flag for checking update of bound */
  string _name;
};
