#pragma once

#include "CompositeNode.hpp"
#include "NodeVisitor.hpp"
#include "../Include/GLFrame.h"

/**
 * Light represents a light node i the scene.
 * @author Steve Eriksson
 */
class Light : public CompositeNode {
public:

  /** 
   * Create a default light object.
   * The light will be positioned at the origin, pointing down -z axle
   * having the y-axle as the up vector. The light will be off.
   */
  Light();

  /** 
   * Create a light and initialize the position and direction of it and
   * set it's parent.
   * The light will be off.
   *
   * @param M3DVector3f position
   * @param M3DVector3f direction
   * @param Node        pointer to parent node
   */
  Light( const M3DVector3f, const M3DVector3f, Node* );

  ~Light() {};

  /** Accept a visitor */
  void Accept( NodeVisitor* );

  /**
   * Set the direction of the light.
   * @param M3DVector3f
   */
  void SetDirection( const M3DVector3f );

  /**
   * Set the position/origin of the light.
   * @param M3DVector3f
   */
  void SetPostition( const M3DVector3f );

  /**
   * Set the diffuse light component.
   * @param M3DVector4f  RGBA
   */
  void SetDiffuse( const M3DVector4f );

  /**
   * Set the ambient light component.
   * @param M3DVector4f  RGBA
   */
  void SetAmbient( const M3DVector4f );

  /**
   * Set the specular light component.
   * @param M3DVector4f  RGBA
   */
  void SetSpecular( const M3DVector4f );

  /**
   * Get the lights position/origin.
   * @param M3DVector3f a vector to assign the position to.
   */
  void GetPosition( M3DVector3f ) const;

  /**
   * Get the lights direction.
   * @param M3DVector3f a vector to assign the direction to.
   */
  void GetDirection( M3DVector3f ) const;

  /**
   * Get the light's diffuse component.
   * @param M3DVector3f a vector to assign the component to.
   */
  void GetDiffuse( M3DVector4f ) const;

  /**
   * Get the light's ambient component.
   * @param M3DVector3f a vector to assign the component to.
   */
  void GetAmbient( M3DVector4f ) const;

  /**
   * Get the light's specular component.
   * @param M3DVector3f a vector to assign the component to.
   */
  void GetSpecular( M3DVector4f ) const;

private:
  GLFrame     _frame;    /**< Handles position, direction and movement of the light. */
  M3DVector4f _ambient;  /**< Ambient component. RGBA.  */
  M3DVector4f _diffuse;  /**< Diffuse component. RGBA.  */
  M3DVector4f _specular; /**< Specular component. RGBA. */
  
  /** initialize light component vectors */
  void Init();
};
