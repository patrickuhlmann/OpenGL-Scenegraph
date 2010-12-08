#include "RenderVisitor.hpp"


// Initialize the ModelView and Projection matrix stacks
// Projection is derived by a given frustum that can 
// be provided by a Camera
RenderVisitor::RenderVisitor( const GLFrustum& frustum )
{
  _projectionMatrix.LoadMatrix( frustum.GetProjectionMatrix );
  _transformPipeline.SetMatrixStacks( _modelViewMatrix, _projectionMatrix );
}

