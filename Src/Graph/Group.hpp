#pragma once
#include "CompositeNode.hpp"
#include <string>
#include <glog/logging.h>

/** \brief This class is a compositeNode which is only to group other nodes. It has no other function */
class Group : public CompositeNode {
public:
	virtual ~Group();
	Group( const std::string& );
	virtual void Accept( NodeVisitor* );
};
