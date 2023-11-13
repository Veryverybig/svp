#ifndef SVP_NODEVISITOR_H
#define SVP_NODEVISITOR_H

#include "Node.h"

namespace svp
{


class NodeVisitor {
public:
    virtual void visit(const Node &root) = 0;
    virtual ~NodeVisitor() = default;

protected:
    void addIndent(std::stringstream &ss) const;

protected:
    int indent = 0;
    bool is_last_field = false;
    bool is_last_interface = false;
};


class GenModuleVisitor : public NodeVisitor {
public:
    GenModuleVisitor(const std::string &filename);

    void processInterface(const Node &node);
    void processField(const Node &node, const Node &interface);

    void visit(const Node &root) override;

public:
    std::string filename;
};


class GenInterfaceVisitor :  public NodeVisitor {
public:
    void processInterface(const Node &node);

    void visit(const Node &root) override;
};




} // namespace svp




#endif // SVP_NODEVISITOR_H