#pragma once
#include "CompositeNode.hpp"
#include <string>

class Group : public CompositeNode {
public:
   Group( const std::string& );
   virtual void Accept( NodeVisitor* );
};
