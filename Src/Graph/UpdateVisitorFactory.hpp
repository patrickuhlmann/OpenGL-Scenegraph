#pragma once
#include "TransformUpdateVisitor.hpp"
#include "RotateTransformStrategy.hpp"
#include "ScaleTransformStrategy.hpp"
#include "TranslateTransformStrategy.hpp"

enum VisitorType { ROTATE, SCALE, TRANSLATE };

class UpdateVisitorFactory {
public:
   NodeVisitor* CreateTransformationVisitor( VisitorType type, float x, float y, float z, float angle = 0.0f );

private:
   NodeVisitor* CreateRotateVisitor( float x, float y, float z, float angle );
   NodeVisitor* CreateScaleVisitor( float x, float y, float z, float angle = 0.0f );
   NodeVisitor* CreateTranslateVisitor( float x, float y, float z, float angle = 0.0f );
};
