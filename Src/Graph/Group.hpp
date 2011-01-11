#pragma once
#include "CompositeNode.hpp"
#include <string>
#include <glog/logging.h>

class Group : public CompositeNode {
public:
   ~Group();
   Group( const std::string& );
   virtual void Accept( NodeVisitor* );
};
