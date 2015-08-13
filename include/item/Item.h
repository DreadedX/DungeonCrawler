#ifndef ITEM_H
#define ITEM_H

struct ItemTypeData {

    std::string name;
    float value;
    float weight;
    const ItemUsageClass *usage;
};

struct MaterialData {

    std::string name;
    float value;
    float weight;
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

// TODO: Load all of this from a file
static const ItemTypeData itemTypes[] = { 
    { "Empty", 0, 0, &ItemUsage::NONE },
    { "Sword", 10, 2, &ItemUsage::MELEE },
    { "Bow", 15, 1, &ItemUsage::RANGED },
    { "Ring", 5, 0.5f, &ItemUsage::NONE }
};
static const int itemTypeCount = sizeof(itemTypes)/sizeof(ItemTypeData);

static const MaterialData materials[] = { 
    { "", 0, 0 },
    { "Wooden", 0.1f, 0.1f },
    { "Iron", 1, 1 },
    { "Golden", 1.2f, 1.1f }
};
static const int materialCount = sizeof(materials)/sizeof(MaterialData);

static const ModifierData modifiers[] = { 
    { "", 1, 1 },
    { "Great", 1.1f, 0.9f },
    { "Terrible", 0.5f, 1.1f },
    { "Godly", 2, 0.5f },
    { "Moldy", 0.7f, 1}
};
static const int modifierCount = sizeof(modifiers)/sizeof(ModifierData);

static const EnchantmentData enchantments[] = { 
    { "", 1, 1, true },
    { "Flaming", 1.5f, 1, true },
    { "Regeneration", 1.1f, 1, false },
    { "Lucky", 1.2f, 0.9f, true }
};
static const int enchantmentCount = sizeof(enchantments)/sizeof(EnchantmentData);

class Item {

    public: 

	Item(int level = 1, const ItemTypeData *itemType = &itemTypes[0], const MaterialData *material = &materials[0], const ModifierData *modifier = &modifiers[0], const EnchantmentData *enchantment = &enchantments[0]);

	std::string getName() {

	    return name;
	}

	int getLevel() {

	    return level;
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
	int level;
	float value;
	float weight;

	const ItemTypeData *itemType;
	// const MaterialData *material;
	// const ModifierData *modifier;
	// const EnchantmentData *enchantment;
};

#endif

