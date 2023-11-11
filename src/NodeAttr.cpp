#include "NodeAttr.h"

namespace svp
{

NodeAttr::NodeAttr(const KeyType &key, const ValueType &value)
    : ValueType(value), key(key) {}

} // namespace svp


