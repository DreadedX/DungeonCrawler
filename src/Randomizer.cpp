# include "Standard.h"

namespace Randomizer {

    void init() {

	srand(time(NULL));
    }

    Item item() {

	int random = -1;

	const ItemTypeData *itemType;
	const ModifierData *modifier;
	const EnchantmentData *enchantment;

	random = (int) (rand() % 2);
	switch (random) {
	    case 0:
		itemType = &ItemType::SWORD;
		break;

	    case 1:
		itemType = &ItemType::BOW;
		break;
	}

	random = (int) (rand() % 3);
	switch (random) {
	    case 0:
		modifier = &Modifier::NONE;
		break;

	    case 1:
		modifier = &Modifier::AWESOME;
		break;

	    case 2:
		modifier = &Modifier::TERRIBLE;
		break;
	}

	random = (int) (rand() % 3);
	switch (random) {
	    case 0:
		enchantment = &Enchantment::NONE;
		break;

	    case 1:
		enchantment = &Enchantment::FLAMING;
		break;

	    case 2:
		enchantment = &Enchantment::REGENERATION;
		break;
	}

	Item item(itemType, modifier, enchantment);

	return item;
    }
};
