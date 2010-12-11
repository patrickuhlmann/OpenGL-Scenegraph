#pragma once

#include "Node.hpp"
#include "../Base/Mesh.hpp"
#include "NodeVisitor.hpp"
#include "State.hpp"

/**
 * A leaf node representing a graphical object.
 */
class Geometry : public Node {
public:
  Geometry() { _dirty = false; }; // accept geometry without mesh?
  Geometry( Mesh*, Node* );
  ~Geometry(); // Delete mesh?

  /** Accept a visitor */
  void Accept( NodeVisitor* );

  /** Set the mesh pointer */
  void SetMesh( Mesh* );

  /** Return the mesh pointer */
  Mesh* GetMesh() { return _mesh; };

private:
  Mesh* _mesh; /**< Pointer to a mesh */
  State _state;
  //bool  _dirty; /**< Flag for checking update of bound */
 }
