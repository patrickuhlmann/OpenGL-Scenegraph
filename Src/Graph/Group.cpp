#include "Group.hpp"

/** \brief Create a group node with a name
 * \param Name of the Node */
Group::Group(const std::string& Name) : CompositeNode( Name ) {}

/** \brief Accept a Visitor. Just call the VisitGroup Method
 * \param Visitor who visits us
 */
void Group::Accept( NodeVisitor* Visitor )
{
   Visitor->VisitGroup( this );
}

/** \brief Empty Destructor */
Group::~Group() {
	DLOG(INFO) << "~Group" << endl;
}
