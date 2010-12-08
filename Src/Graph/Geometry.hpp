#pragma once

#include "Node.hpp"
#include "Mesh.hpp"

class Geometry : public Node {
public:
  Geometry() { _dirty = false; }; // accept geometry without mesh?
  Geometry( Mesh*, Node* );
  ~Geometry(); // Delete mesh?

  void Accept( NodeVisitor* );
  void SetMesh( Mesh* );

  Mesh* GetMesh() { return _mesh; };

private:
  Mesh* _mesh;
  bool  _dirty;
}
