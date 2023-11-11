#ifndef SVP_NODEATTR_H
#define SVP_NODEATTR_H

#include <variant>
#include <string>
#include <vector>
#include <optional>

namespace svp
{
    





class NodeAttr : public std::variant<bool, int, std::string> {
public:
    using KeyType = std::string;
    using ValueType = std::variant<bool, int, std::string>;

    std::string key;

    NodeAttr(const KeyType &key, const ValueType &value);
};

using NodeAttrList = std::vector<NodeAttr>;
using NodeAttrOpt = std::optional<NodeAttr>;

} // namespace svp

#endif // SVP_NODEATTR_H