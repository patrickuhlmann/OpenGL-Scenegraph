#include "Torus.h"

/** \brief Create a Torus
  * \param MajorRadius to the outer circle
  * \param MinorRadius to the inner circle
  * \param MajorNum number of subdivisions for the big circle
  * \param MinorNum number of subdivisions for the small circle */
Torus::Torus(float MajorRadius, float MinorRadius, int MajorNum, int MinorNum) {
	Material* Mat = new Material("CubeMat", Vector3(1.0f, 0, 0));
	Mat->SetDiffuse(Vector3(0, 0.3f, 0));
	_materials.insert(mmsm::value_type("CubeMat", Mat));

    double MajorStep = 2.0f * PI / MajorNum;
    double MinorStep = 2.0f * PI / MinorNum;
    int i, j;
	
    for (i=0; i<MajorNum; ++i) {
		double a0 = i * MajorStep;
		double a1 = a0 + MajorStep;
		float x0 = cos(a0);
		float y0 = sin(a0);
		float x1 = cos(a1);
		float y1 = sin(a1);

		

		M3DVector3f vVertex[4];
		M3DVector3f vNormal[4];
		M3DVector2f vTexture[4];
		
		for (j=0; j<=MinorNum; ++j) {
			double b = j * MinorStep;
			float c = cos(b);
			float r = MinorRadius * c + MajorRadius;
			float z = MinorRadius * sin(b);
			
			// First point
			/*Vector3* Normal1 = new Vector3(x0*c, y0*c, z/minorRadius)
			m3dNormalizeVector3(vNormal[0]);*/
			Vector3* Point1 = new Vector3(x0 * r, y0 * r, z);
			_vertices.push_back(Point1);
			
			// Second point
			/*Vector3* Normal2 = new Vector3(x1*c, y1*c, z/minorRadius)
			m3dNormalizeVector3(vNormal[1]);*/
			Vector3* Point2 = new Vector3(x1 * r, y1 * r, z );
			_vertices.push_back(Point2);

			// Next one over
			b = (j+1) * MinorStep;
			c = cos(b);
			r = MinorRadius * c + MajorRadius;
			z = MinorRadius * sin(b);
						
			// Third (based on first)
			/*Vector3* Normal3 = new Vector3(x0*c, y0*c, z/minorRadius);
			m3dNormalizeVector3(vNormal[2]);*/
			Vector3* Point3 = new Vector3(x0 * r, y0 * r, z);
			_vertices.push_back(Point3);
			
			// Fourth (based on second)
			/*Vector3* Normal3 = new Vector3(x1*c, y1*c, z/minorRadius)
			m3dNormalizeVector3(vNormal[3]);*/
			Vector3* Point4 = new Vector3(x1*r, y1*r, z);
			_vertices.push_back(Point4);

			_triangles.push_back(new Triangle(Point1, Point2, Point3, Vector3(x0*c, y0*c, z/MinorRadius), Mat));
	
			
			// Rearrange for next triangle
			Point1 = new Vector3(Point2);
			Point2 = new Vector3(Point4);
			Point3 = new Vector3(Point3);
			_vertices.push_back(Point1);
			_vertices.push_back(Point2);
			_vertices.push_back(Point3);

			_triangles.push_back(new Triangle(Point1, Point2, Point3, Vector3(x1*c, y1*c, z/MinorRadius), Mat));		
		}
	}
}
