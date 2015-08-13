# include "Standard.h"

namespace Randomizer {

    int random(long *seed) {

	*seed = (*seed * 32719 + 3) % 32749;

	return *seed + 1;
    }

    int random(int max, long *seed) {

	return ((random(seed)-1) % max) + 1;
    }

    Item item() {

	static long seedItem = time(NULL);

	const ItemTypeData *itemType;
	const MaterialData *material;
	const ModifierData *modifier;
	const EnchantmentData *enchantment;

	itemType = &itemTypes[random(itemTypeCount - 1, &seedItem)];
	material = &materials[random(materialCount - 1, &seedItem)];
	modifier = &modifiers[random(modifierCount, &seedItem) - 1];
	enchantment = &enchantments[random(enchantmentCount, &seedItem) - 1];

	Item item(random(20, &seedItem), itemType, material, modifier, enchantment);

	return item;
    }
};
