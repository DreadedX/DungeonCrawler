#ifndef ITEM_H
#define ITEM_H

struct ItemComponent : Component {

    ItemComponent(int id);

    std::string name;
    float value;
    float weight;
};

struct ModifierItemComponent : Component {

    ItemComponent *item = nullptr;

    ModifierItemComponent(int id);

    std::string name = "";
    float value = 1;
    float weight = 1;

    void init() override;
};

struct EnchantmentItemComponent : Component {

    ItemComponent *item = nullptr;

    std::string name = "";
    float value = 1;
    float weight = 1;

    void init() override;
};

struct UsageItemComponent : Component {

    ItemComponent *item = nullptr;
    // TODO: Make this do something
};

struct FlamingEnchantment : EnchantmentItemComponent {
    
    FlamingEnchantment() {

	name = "Flaming";
	value = 2;
	weight = 0.9f;
    }
};

struct MeleeWeapon : UsageItemComponent {
    
    // TODO: Make this do something
};

#endif

