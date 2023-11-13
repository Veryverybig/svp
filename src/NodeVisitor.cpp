#include "NodeVisitor.h"

#include <iostream>
#include <sstream>

namespace svp
{

void NodeVisitor::addIndent(std::stringstream &ss) const {
    ss << std::string(4 * indent, ' ');
}

GenModuleVisitor::GenModuleVisitor(const std::string &filename)
    : filename(filename) {}

void GenModuleVisitor::processInterface(const Node &node) {
    std::stringstream ss;
    addIndent(ss);
    ss << "// " << node.name << "\n";
    std::cout << ss.str();
}

void GenModuleVisitor::processField(const Node &node, const Node &interface) {
    std::stringstream ss;
    addIndent(ss);
    if(node.getAttrString("direction") == "tx")
        ss << "output ";
    else
        ss << "input  ";
    ss << "logic";
    ss << "[" << node.getAttrInt("packed") << "-1:0] ";
    ss << interface.name << "_" << node.name;
    ss << (is_last_field ? "\n" : ",\n");

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
                    is_last_field = true;
                processField(*f, *i);
            }
        }
    }

    std::cout << ");\n";
    indent--;
    std::cout << "endmodule\n";
}

void GenInterfaceVisitor::processInterface(const Node &node) {
    std::stringstream ss;
    ss << "interface " << node.name << ";\n";
    indent++;
    for(auto &f : node.children) {
        addIndent(ss);
        ss << "logic[" << f.getAttrInt("packed") - 1 << ":0] " << f.name << ";\n";
    }

    // modport tx
    addIndent(ss); ss << "modport tx(\n";
    indent++;
    for(auto &f : node.children) {
        addIndent(ss);
        if(f.getAttrString("direction") == "tx")
            ss << "output " << f.name;
        else
            ss << "input  " << f.name;
        ss << (is_last_field ? "\n" : ",\n");
    }
    indent--;
    addIndent(ss); ss << ");\n";


    // modport rx
    addIndent(ss); ss << "modport rx(\n";
    indent++;
    for(auto &f : node.children) {
        addIndent(ss);
        if(f.getAttrString("direction") == "rx")
            ss << "output " << f.name;
        else
            ss << "input  " << f.name;
        ss << (is_last_field ? "\n" : ",\n");
    }
    indent--;
    addIndent(ss); ss << ");\n";

    ss << "endinterface";

    std::cout << ss.str();
}

void GenInterfaceVisitor::visit(const Node &root) {
    for(auto i = root.children.cbegin(), ie = root.children.cend(); i != ie; i++) {
        if(i->kind == NodeKind::INTERFACE) {
            processInterface(*i);
        }
    }
}



} // namespace svp
