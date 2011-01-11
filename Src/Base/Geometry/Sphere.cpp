#include "Sphere.h"

Material Sphere::SphereMaterial = Material("SphereMat", Vector3(0, 0, 1.0f), Vector3(0.3f, 0, 0));

/** \brief Create a sphere at the origin
 * \param Radius of the sphere
 * \param Slices on the x surface
 * \param Stacks on the y surface
 */
Sphere::Sphere(float Radius, int Slices, int Stacks) : Mesh() {
	Init(Radius, Slices, Stacks);
}

/** \brief Create a sphere at the origin
 * \param Radius of the sphere
 * \param Slices on the x surface
 * \param Stacks on the y surface
 * \param Name of the Sphere
 * \param Mat Material to use. Default is SphereMat
 */
Sphere::Sphere(float Radius, int Slices, int Stacks, const string& Name, const Material& Mat) : Mesh(Name) {
	Init(Radius, Slices, Stacks, Mat);
}

/** \brief Create a sphere at the origin
 * \param Radius of the sphere
 * \param Slices on the x surface
 * \param Stacks on the y surface
 * \param Name of the Sphere
 * \param Mat Material to use. Default is SphereMat
 */
void Sphere::Init(float Radius, int Slices, int Stacks, const Material& SMat) {
	Material* Mat = new Material(SMat);
	_materials.insert(mmsm::value_type("SphereMat", Mat));

    float drho = PI / (float)Stacks;
    float dtheta = 2.0f * PI  / (float)Slices;
	float ds = 1.0f / (float) Slices;
	float dt = 1.0f / (float) Stacks;
	float t = 1.0f;	
	float s = 0.0f;
    int i, j;     // Looping variables
    
	for (i = 0; i < Stacks; i++) {
		float rho = (float)i * drho;
		float srho = sin(rho);
		float crho = cos(rho);
		float srhodrho = sin(rho + drho);
		float crhodrho = cos(rho + drho);
		
        // Many sources of OpenGL sphere drawing code uses a triangle fan
        // for the caps of the sphere. This however introduces texturing 
        // artifacts at the poles on some OpenGL implementations
        s = 0.0f;

		for ( j = 0; j < Slices; j++) 
			{
			float theta = (j == Slices) ? 0.0f : j * dtheta;
			float stheta = -sin(theta);
			float ctheta = cos(theta);
			
			float x = stheta * srho;
			float y = ctheta * srho;
			float z = crho;
        
			Vector3 Normal1 = Vector3(x, y, z);
			Vector3* Point1 = new Vector3(x * Radius, y * Radius, z * Radius);
			_vertices.push_back(Point1);
			
            x = stheta * srhodrho;
			y = ctheta * srhodrho;
			z = crhodrho;

			Vector3 Normal2 = Vector3(x, y, z);
			Vector3* Point2 = new Vector3(x * Radius, y * Radius, z * Radius);
			_vertices.push_back(Point2);

			theta = ((j+1) == Slices) ? 0.0f : (j+1) * dtheta;
			stheta = -sin(theta);
			ctheta = cos(theta);
			
			x = stheta * srho;
			y = ctheta * srho;
			z = crho;
        
            s += ds;
			//Vector3 Normal3 = Vector3(x, y, z);
			Vector3* Point3 = new Vector3(x * Radius, y * Radius, z * Radius);
			_vertices.push_back(Point3);
			
            x = stheta * srhodrho;
			y = ctheta * srhodrho;
			z = crhodrho;

			Vector3 Normal4 = Vector3(x, y, z);
			Vector3* Point4 = new Vector3(x * Radius, y * Radius, z * Radius);
			_vertices.push_back(Point4);

			_triangles.push_back(new Triangle(Point1, Point2, Point3, Normal1, Mat));

			// Rearrange for next triangle
			Point1 = new Vector3(Point2);
			Point2 = new Vector3(Point4);
			Point3 = new Vector3(Point3);
			_vertices.push_back(Point1);
			_vertices.push_back(Point2);
			_vertices.push_back(Point3);

			_triangles.push_back(new Triangle(Point1, Point2, Point3, Normal2, Mat));			
		}

		t -= dt;
	}
}
