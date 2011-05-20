#include "Node.hpp"

int Node::NodeCounter = 0;

/** \brief Default Constructor sets parent to 0 and generates a name Node + NodeNumber */
Node::Node() {
	_parent = 0;
	_name = string("Node" + NodeCounter);
	NodeCounter++;
};

/** \brief Creates a node with the specified name which has no parent
 * \param name of the Node
 */
// TODO: warning if node name already used before
Node::Node(string name) {
	_parent = 0;
	_name = string(name);
	NodeCounter++;
}

/** \brief Destructor. Empty */
Node::~Node() {
	DLOG(INFO) << "~Node for " << this->GetName() << endl;
}

/** \brief Set the Parent of this Node. You cannot set yourself as parent
*
* \param Parent pointer to the parent node
*/
void Node::SetParent(Node* Parent) {
	_parent = Parent;
}

/** \brief Get the Parent of this Node. It can also be 0 when there is no parent */
const Node* Node::GetParent() const {
	return _parent;
}

/** \brief Get the Name of this node. If it had no name "" will be returned */
const string& Node::GetName() const {
	return this->_name;
}

