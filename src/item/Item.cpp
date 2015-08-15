# include "Standard.h"

void ModifierItemComponent::init() {

    item = &entity->getComponent<ItemComponent>();

    item->name = String::format("%s %s", name.c_str(), item->name.c_str());
    item->value *= value;
    item->weight *= weight;
}


void EnchantmentItemComponent::init() {

    item = &entity->getComponent<ItemComponent>();

    item->name = String::format("%s %s", name.c_str(), item->name.c_str());
    item->value *= value;
    item->weight *= weight;
}
