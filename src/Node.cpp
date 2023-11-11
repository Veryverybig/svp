#include "Node.h"

#include <iostream>
#include <sstream>

namespace svp
{

Node::Node(const std::string &name, NodeKind kind)
    : name(name), kind(kind) {}

std::string Node::toString() const {
    std::stringstream ss;
    ss << NodeKindString[kind] << " " << name;
    return ss.str();
}

std::ostream &operator<<(std::ostream &os, const Node &node) {
    os << node.toString() << "\n";
    for(auto &c : node.children) {
        os << c;
    }

    return os;
}


} // namespace svp

