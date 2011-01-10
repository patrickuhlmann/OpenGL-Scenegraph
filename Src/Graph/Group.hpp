#pragma once
#include "CompositeNode.hpp"
#include <string>
#include <glog/logging.h>
#include "../../Libs/nvwa-0.8.2/debug_new.h"

class Group : public CompositeNode {
public:
   ~Group();
   Group( const std::string& );
   virtual void Accept( NodeVisitor* );
};
