#ifndef ITEM_H
#define ITEM_H

struct ItemTypeData {

    std::string name;
    float value;
    float weight;
    const ItemUsageClass *usage;
};

struct ModifierData {

    std::string name;
    float valueModifier;
    float weightModifier;
};

struct EnchantmentData {

    std::string name;
    float valueModifier;
    float weightModifier;
    bool prefix;
    // ItemPassiveClass *passive;
};

class Item {

    public: 

	Item(const ItemTypeData *itemType, const ModifierData *modifier, const EnchantmentData *enchantment);

	std::string getName() {

	    return name;
	}
	
	float getValue() {
	    
	    return value;
	}

	float getWeight() {

	    return weight;
	}

	void use();
	void passive();

    private:

	std::string name;
	float value;
	float weight;
	const ItemTypeData *itemType;
	const ModifierData *modifier;
	const EnchantmentData *enchantment;
};

namespace ItemType {

    static const ItemTypeData NONE = { 
	"Empty", 0, 0, &ItemUsage::NONE
    };

    static const ItemTypeData SWORD = { 
	"Sword", 10, 2, &ItemUsage::MELEE
    };

    static const ItemTypeData BOW = {
	"Bow", 15, 1, &ItemUsage::RANGED
    };
};

namespace Modifier {

    static const ModifierData NONE = { 
	"", 1, 1
    };

    static const ModifierData AWESOME = { 
	"Awesome", 10, 1
    };

    static const ModifierData TERRIBLE = {
	"Terrible", 0.5f, 1.1f
    };
};

namespace Enchantment {

    static const EnchantmentData NONE = { 
	"", 1, 1, true
    };

    static const EnchantmentData FLAMING = { 
	"Flaming", 1.5f, 1, true
    };

    static const EnchantmentData REGENERATION = {
	"Regeneration", 1.1f, 1, false
    };
};

#endif

