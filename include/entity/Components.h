#ifndef COMPONENTS_H
#define COMPONENTS_H

struct PositionComponent : Component {

    vec4 position;
    PositionComponent(vec4 mPosition);
};

struct PhysicsComponent : Component {

    const float frictionFloat = pow(0.8f, 1/VT);
    const mat4 friction = scale(mat4(IDENTITY), vec3(frictionFloat));

    PositionComponent *cPosition = nullptr;

    vec4 velocity = vec4(0, 0, 0, 0);

    void init() override;
    void tick() override;

    float getAccelaration(float maxSpeed) {

	return (maxSpeed) / (1 / (1 - frictionFloat)) * VT;
    }
};

struct TextureComponent : Component {

    PositionComponent *cPosition = nullptr;

    TextureComponent(std::string mTex, vec4 mScale);

    GLuint tex = 0;
    vec4 scale;

    void init() override;
    void render() override;
};

struct InventoryComponent : Component {

    Manager inventory;

    InventoryComponent() {

	Entity &item = inventory.addEntity();
	item.addComponent<ItemComponent>("Sword", 10, 2);
	item.addComponent<FlamingEnchantment>();
	item.addComponent<ModifierItemComponent>("Awesome", 2, 0.8f);
    }

    // bool addItem(Item item);
    // void removeItem(int slot);
    void listInventory();
};

struct PlayerComponent : Component {

    PhysicsComponent *cPhysics = nullptr;

    float acceleration = 0;

    void init() override;
    void tick() override;
};

#endif

