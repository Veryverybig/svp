#ifndef SVP_NODEVISITOR_H
#define SVP_NODEVISITOR_H

#include "Node.h"

namespace svp
{


class NodeVisitor {
public:
    virtual void visit(const Node &root) = 0;
    virtual ~NodeVisitor() = default;
};


class GenModuleVisitor : public NodeVisitor {
public:
    GenModuleVisitor(const std::string &filename);

    void processInterface(const Node &node);
    void processField(const Node &node, const Node &interface);

    void visit(const Node &root) override;

public:
    std::string filename;

private:
    int indent = 0;
    bool is_lastfield = false;
};


class GenInterfaceVisitor :  public NodeVisitor {

};




} // namespace svp




#endif // SVP_NODEVISITOR_H