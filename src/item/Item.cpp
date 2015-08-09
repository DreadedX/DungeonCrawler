# include "Standard.h"

Item::Item(const ItemTypeData *itemType, const ModifierData *modifier, const EnchantmentData *enchantment) {

    if (enchantment->name != "") {
	if (enchantment->prefix) {

	    this->name = String::format("%s %s", enchantment->name.c_str(), itemType->name.c_str());
	} else {

	    this->name = String::format("%s of %s", itemType->name.c_str(), enchantment->name.c_str());
	}
    } else {

	this->name = itemType->name.c_str();
    }

    if (modifier->name != "") {

	this->name = String::format("%s %s", modifier->name.c_str(), this->name.c_str());
    }

    this->value = itemType->value * modifier->valueModifier * enchantment->valueModifier;
    this->weight = itemType->weight * modifier->weightModifier * enchantment->weightModifier;

    this->itemType = itemType;
    this->modifier = modifier;
    this->enchantment = enchantment;
}

void Item::use() {

    this->itemType->usage->use();
}
