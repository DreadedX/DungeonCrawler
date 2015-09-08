#include "Standard.h"

struct MeleeAttack : ItemType {

    void attack() override {

	Log::print("Melee attack", DEBUG);
    }
};

struct ArrowAttack : ItemType {

    void attack() override {

	// NOTE: Maybe make this a delay, that way you don't have to spawn the mouse button
	Input::setState(GLFW_MOUSE_BUTTON_LEFT, false);
	auto& projectile = Level::getManager()->addEntity();
	projectile.addComponent<PositionComponent>(Level::getPlayer()->getComponent<PositionComponent>().position);
	projectile.addComponent<HitboxComponent>(glm::vec4(0, 0, 0, 0), glm::vec4(1, 1, 1, 0));
	projectile.addComponent<CollisionComponent>();
	projectile.addComponent<PhysicsComponent>();
	float angle = Math::pointAngle(glm::vec4(WIDTH*SCALE/2, HEIGHT*SCALE/2, 0, 1), Input::getMousePos());
	projectile.addComponent<TextureComponent>("entity/arrow", glm::vec4(17.0f/16.0f, 20.0f/16.0f, 1, 0), angle);
	projectile.addComponent<ProjectileComponent>(glm::vec4(0.25 * cos(angle), 0.25 * sin(angle), 0, 0));
    }
};

struct HealingPassive : ItemType {

    void passive() override {

	Level::getPlayer()->getComponent<HealthComponent>().heal(0.05f);
    }
};

ItemComponent::ItemComponent(int id) {

    // TODO: Move this into a seperate function
    static int itemsID = Reader::getId("config/items");
    static byte json[1000] = {0x00};
    static rapidjson::Document d;

    if (json[0] == 0x00) {
	Reader::read(itemsID, json);

	d.Parse(reinterpret_cast<char const*>(json));
    }

    static rapidjson::Value &i = d["items"];
    rapidjson::Value &item = i[id];

    name = item[0].GetString();
    value = item[1].GetDouble();
    weight = item[2].GetDouble();
	    
    // TODO: Add delete for each new
    // TODO: There has to be a better way to do this
    switch (item[3].GetInt()) {

	// NOTE: If attack() deal damage in close range of player
	case TYPE_MELEE:
	    itemType = new MeleeAttack;
	    break;

	// NOTE: If attack() spawn projectile
	case TYPE_RANGED:
	    Log::print("Ranged weapon", DEBUG);
	    itemType = new ArrowAttack;
	    break;

	// NOTE: If passive() execute passive code
	case TYPE_PASSIVE:
	    HealingPassive healingPassive;
	    itemType = new HealingPassive;
	    break;
    }
}

void ItemComponent::attack() {

    Log::print("Attacking", DEBUG);
    itemType->attack();
}

void ItemComponent::passive() {

    itemType->passive();
}

ModifierItemComponent::ModifierItemComponent(int id) {

    // TODO: Move this into a seperate function
    static int itemsID = Reader::getId("config/items");
    static byte json[1000] = {0x00};
    static rapidjson::Document d;

    if (json[0] == 0x00) {
	Reader::read(itemsID, json);
    
	d.Parse(reinterpret_cast<char const*>(json));
    }

    static rapidjson::Value &m = d["modifiers"];
    rapidjson::Value &modifier = m[id];

    name = modifier[0].GetString();
    value = modifier[1].GetDouble();
    weight = modifier[2].GetDouble();
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
