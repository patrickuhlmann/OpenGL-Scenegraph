#pragma once

#include "../Mesh.hpp"

/** \brief class to create a mesh containing a Torus */
class Torus : public Mesh {
	private:
		void Init(float MajorRadius, float MinorRadius, int MajorNum, int MinorNum, const Material& TMat = TorusMaterial);
		/** \brief Holds a prototype material to use for torus. It's red with green diffuse component */
		static Material TorusMaterial;

	public:
		Torus(float MajorRadius, float MinorRadius, int MajorNum, int MinorNum);
		Torus(float MajorRadius, float MinorRadius, int MajorNum, int MinorNum, const string& Name, const Material& Mat = TorusMaterial);

};
