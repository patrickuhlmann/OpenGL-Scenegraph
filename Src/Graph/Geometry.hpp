#pragma once

#include "CompositeNode.hpp"
#include "../Base/Mesh.hpp"
#include "../Base/State.hpp"
#include <string>

using namespace std;

/**
 * A leaf node representing a graphical object.
 */
class Geometry : public CompositeNode {
public:
	Geometry(Mesh* M);
	Geometry(Mesh* M, const string& Name);
	virtual ~Geometry();

	void Accept( NodeVisitor* );

	void SetMesh( Mesh* );
	const Mesh* GetMesh() const;

	void SetState(State*);
	const State* GetState() const;

	void SetVisibility(bool NewStatus);
	bool GetVisibility() const;

private:
	/** \brief Pointer to the Mesh of this Geometry */
	Mesh* _mesh;
	/** \brief Pointer to the State of this Geometry */
	State* _state;
	/** \brief Holds the Visiblilty Status of this Geometry */
	bool Visible;
};
