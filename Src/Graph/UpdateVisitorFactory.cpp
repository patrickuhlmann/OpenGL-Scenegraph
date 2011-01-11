#include "UpdateVisitorFactory.hpp"

 NodeVisitor* UpdateVisitorFactory::CreateTransformationVisitor( VisitorType type, float x, float y, float z, float angle )
{
   NodeVisitor* n = 0;

   switch( type ) {
      case ROTATE:
         n = CreateRotateVisitor( x, y, z, angle );
         break;
      case SCALE:
         n = CreateScaleVisitor( x, y, z, angle );
         break;
      case TRANSLATE:
         n = CreateTranslateVisitor( x, y, z, angle );
         break;
      default:
         break;
   }

   return n;
}

 NodeVisitor* UpdateVisitorFactory::CreateRotateVisitor( float x, float y, float z, float angle )    
{ return new TransformUpdateVisitor( RotateTransformStrategy( angle, x, y, z ) ); }

 NodeVisitor* UpdateVisitorFactory::CreateScaleVisitor( float x, float y, float z, float angle )     
{ return new TransformUpdateVisitor( ScaleTransformStrategy( x, y, z ) ); }

 NodeVisitor* UpdateVisitorFactory::CreateTranslateVisitor( float x, float y, float z, float angle ) 
{ return new TransformUpdateVisitor( TranslateTransformStrategy( x, y, z ) ); }
