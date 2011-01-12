#include "TransformStrategy.hpp"
#include "glog/logging.h"
#include <iostream>

using namespace std;

TransformStrategy::TransformStrategy() { m3dLoadIdentity44( _transMatrix ); }

//void TransformStrategy::transformation() { DLOG(INFO) }

void TransformStrategy::Apply( Transform* t )
{
   M3DMatrix44f newMatrix, oldMatrix;
   t->GetMatrix( oldMatrix );

   // Use hook to perform custom transformation of matrix
   transformation();

   // result, a, b
   m3dMatrixMultiply44( newMatrix, oldMatrix, _transMatrix );

   t->SetMatrix( newMatrix );
}
