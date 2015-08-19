#ifndef COMPONENTS_H
#define COMPONENTS_H

struct PositionComponent : Component {

    vec4 position;
    PositionComponent(vec4 mPosition);
};

struct HitboxComponent : Component {

    vec4 origin;
    vec4 size;

    HitboxComponent(vec4 mOrigin, vec4 mSize);
};

struct CollisionComponent : Component {

    PositionComponent *cPosition = nullptr;
    HitboxComponent *cHitbox = nullptr;

    void init() override;

    mat4 checkCollision(vec4 mVelocity);
};

struct PhysicsComponent : Component {

    const float frictionFloat = pow(0.8f, 1/VT);
    const mat4 friction = scale(mat4(IDENTITY), vec3(frictionFloat));

    PositionComponent *cPosition = nullptr;
    CollisionComponent *cCollision = nullptr;
    bool hasCollision = false;

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

    InventoryComponent();

    int itemCount = 0;
    int modifierCount = 0;

    bool addItem();
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

