#include "TransformStrategy.hpp"

TransformStrategy::TransformStrategy() { m3dLoadIdentity44( _transMatrix ); }

void TransformStrategy::transformation() { /* do nothing */ }

void TransformStrategy::operator() ( Node* c )
{
   Transform* t = dynamic_cast<Transform*>( c );

   if (t) {
      M3DMatrix44f newMatrix, oldMatrix;
      t->GetMatrix( oldMatrix );
      
      // Use hook to perform custom transformation of matrix
      transformation();
      // result, a, b
      m3dMatrixMultiply44( newMatrix, oldMatrix, _transMatrix );

      t->SetMatrix( newMatrix );
   }
}
