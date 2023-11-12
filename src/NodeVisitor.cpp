#include "NodeVisitor.h"

#include <iostream>
#include <sstream>

namespace svp
{

GenModuleVisitor::GenModuleVisitor(const std::string &filename)
    : filename(filename) {}

void GenModuleVisitor::processInterface(const Node &node) {
    std::stringstream ss;
    ss << std::string(4 * indent, ' ');
    ss << "// " << node.name << "\n";
    std::cout << ss.str();
}

void GenModuleVisitor::processField(const Node &node, const Node &interface) {
    std::stringstream ss;
    ss << std::string(4 * indent, ' ');
    if(node.getAttrString("direction") == "tx")
        ss << "output ";
    else
        ss << "input  ";
    ss << "logic";
    ss << "[" << node.getAttrInt("packed") << "-1:0] ";
    ss << interface.name << "_" << node.name;
    ss << (is_lastfield ? "\n" : ",\n");

    std::cout << ss.str();
}

void GenModuleVisitor::visit(const Node &root) {
    std::cout << "module " << filename << "(\n";
    indent++;

    for(auto i = root.children.cbegin(), ie = root.children.cend(); i != ie; i++) {
        if(i->kind == NodeKind::INTERFACE) {
            processInterface(*i);
            for(auto f = i->children.cbegin(), fe = i->children.cend(); f != fe; f++) {
                if(i == ie - 1 && f == fe - 1)
                    is_lastfield = true;
                processField(*f, *i);
            }
        }
    }

    std::cout << ");\n";
    indent--;
    std::cout << "endmodule\n";
}

} // namespace svp
