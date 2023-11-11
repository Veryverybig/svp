#ifndef SVP_NODE_H
#define SVP_NODE_H

#include <vector>
#include <map>
#include <variant>
#include <string>

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
using NodeAttr = std::pair<std::string, std::variant<bool, int, std::string>>;
using NodeAttrList = std::map<std::string, std::variant<bool, int, std::string>>;

class Node {
public:
    std::string name;
    NodeKind kind;

    NodeList children;
    NodeAttrList attrs;

    Node(const std::string &name, NodeKind kind);

    bool hasAttr(const std::string &name) const;
    int getAttrInt(const std::string &name) const;
    bool getAttrBool(const std::string &name) const;
    const std::string &getAttrString(const std::string &name) const;

    std::string toString() const;
};

std::ostream &operator<<(std::ostream &os, const Node &node);


} // namespace svp


#endif // SVP_NODE_H
