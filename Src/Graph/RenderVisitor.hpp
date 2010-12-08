#pragma once

#include "NodeVisitor.hpp"
#include "include/GLTools/GLMatrixStack.h"
#include "include/GLTools/GLTriangleBatch.h"

class RenderVisitor : public NodeVisitor {
public:
  RenderVisitor();
  
  virtual void VisitTransform( Transform* );
  virtual void VisitGeometry ( Geometry* );
  virtual void VisitLight    ( Light* );
  virtual void VisitGroup    ( Group* );
  virtual void VisitCamera   ( Camera* );
  virtual void Traverse( CompositeNode* );
private:
  GLMatrixStack _modelViewMatrix;
  GLMatrixStack _projectionMatrix;
  GLGeometryTransform _transformPipeline;
  ShaderManager _shaderManager;
  Light _light; // Only support one light source at a time right now!
};
