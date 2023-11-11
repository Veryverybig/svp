#include "Node.h"

#include <iostream>
#include <sstream>
#include <algorithm>

namespace svp
{

Node::Node(const std::string &name, NodeKind kind)
    : name(name), kind(kind) {}

bool Node::hasAttr(const std::string &name) const {
    return !attrs.empty() && attrs.find(name) != attrs.cend();
}

int Node::getAttrInt(const std::string &name) const {
    return std::get<int>(attrs.at(name));
}
bool Node::getAttrBool(const std::string &name) const {
    return std::get<bool>(attrs.at(name));
}
const std::string &Node::getAttrString(const std::string &name) const {
    return std::get<std::string>(attrs.at(name));
}

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

