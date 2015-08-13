# include "Standard.h"

Item::Item(int level, const ItemTypeData *itemType, const MaterialData *material, const ModifierData *modifier, const EnchantmentData *enchantment) {

    this->name = itemType->name.c_str();

    if (material->name != "") {

	this->name = String::format("%s %s", material->name.c_str(), this->name.c_str());
    }

    if (enchantment->name != "") {

	if (enchantment->prefix) {

	    this->name = String::format("%s %s", enchantment->name.c_str(), this->name.c_str());
	} else {

	    this->name = String::format("%s of %s", this->name.c_str(), enchantment->name.c_str());
	}
    }

    if (modifier->name != "") {

	this->name = String::format("%s %s", modifier->name.c_str(), this->name.c_str());
    }

    this->level = level;
    this->value = (0.9f + level/10.0f) * itemType->value * modifier->valueModifier * enchantment->valueModifier;
    this->weight = itemType->weight * modifier->weightModifier * enchantment->weightModifier;

    this->itemType = itemType;
    // this->material = material;
    // this->modifier = modifier;
    // this->enchantment = enchantment;
}

void Item::use() {

    this->itemType->usage->use();
}
