#ifndef ITEM_USAGE_H
#define ITEM_USAGE_H

class ItemUsageClass {

    public:

	virtual void use() const = 0;
};

// class ItemPassiveClass {
//
//     public:
//
// 	virtual void passive() = 0;
// };

#include "item/usage/None.h"
#include "item/usage/Ranged.h"
#include "item/usage/Melee.h"

namespace ItemUsage {

    static const None NONE;
    static const Ranged RANGED;
    static const Melee MELEE;
}

// namespace ItemPassive {
//
// }

#endif

