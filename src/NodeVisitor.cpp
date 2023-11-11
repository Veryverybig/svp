#include "NodeVisitor.h"

#include <iostream>
#include <sstream>

namespace svp
{

GenModuleVisitor::GenModuleVisitor(const std::string &filename)
    : filename(filename) {}


void GenModuleVisitor::processField(const Node &node, const Node &interface) {
    std::stringstream ss;
    if(node.getAttrString("direction") == "tx")
        ss << "output ";
    else
        ss << "input  ";
    ss << "logic";
    ss << "[" << node.getAttrInt("packed") << "-1:0] ";
    ss << interface.name << "_" << node.name;
    ss << ",\n";
    std::cout << ss.str();
}

void GenModuleVisitor::visit(const Node &root) {

}

} // namespace svp
