#ifndef SVP_NODE_H
#define SVP_NODE_H

#include <map>

#include "NodeAttr.h"

namespace svp
{

enum class NodeKind : int8_t {
    ROOT,
    INTERFACE,
    FIELD,
};

#define ENTRY(x) {NodeKind::x, #x}
static inline std::map<NodeKind, std::string> NodeKindString {
    ENTRY(ROOT),
    ENTRY(INTERFACE),
    ENTRY(FIELD),
};
#undef ENTRY


class Node;
using NodeList = std::vector<Node>;

class Node {
public:
    std::string name;
    NodeKind kind;

    NodeList children;
    NodeAttrList attrs;

    Node(const std::string &name, NodeKind kind);

    std::string toString() const;
};

std::ostream &operator<<(std::ostream &os, const Node &node);


} // namespace svp


#endif // SVP_NODE_H
