# include "Standard.h"

ItemComponent::ItemComponent(std::string mName, float mValue, float mWeight) {

    name = mName;
    value = mValue;
    weight = mWeight;
}

ModifierItemComponent::ModifierItemComponent(std::string mName, float mValue, float mWeight) {

    name = mName;
    value = mValue;
    weight = mWeight;
}

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
