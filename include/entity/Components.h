#ifndef COMPONENTS_H
#define COMPONENTS_H

struct PositionComponent : Component {

    glm::vec4 position;
    PositionComponent(glm::vec4 mPosition);
};

struct HitboxComponent : Component {

    glm::vec4 origin;
    glm::vec4 size;

    HitboxComponent(glm::vec4 mOrigin, glm::vec4 mSize);
};

struct CollisionComponent : Component {

    PositionComponent *cPosition = nullptr;
    HitboxComponent *cHitbox = nullptr;

    void init() override;

    glm::mat4 checkCollision(glm::vec4 mVelocity);
    bool hasCollided(glm::vec4 mVelocity);
};

struct PhysicsComponent : Component {

    const float frictionFloat = pow(0.8f, 1/VT);
    const glm::mat4 friction = glm::scale(glm::mat4(IDENTITY), glm::vec3(frictionFloat));

    PositionComponent *cPosition = nullptr;
    CollisionComponent *cCollision = nullptr;
    bool hasCollision = false;

    glm::vec4 velocity = glm::vec4(0, 0, 0, 0);

    void init() override;
    void tick() override;

    float getAccelaration(float maxSpeed) {

	return (maxSpeed) / (1 / (1 - frictionFloat)) * VT;
    }
};

struct ProjectileComponent : Component {

    PositionComponent *cPosition = nullptr;
    CollisionComponent *cCollision = nullptr;
    PhysicsComponent *cPhysics = nullptr;

    glm::vec4 velocity;
    int life = 60;

    ProjectileComponent(glm::vec4 mVelocity);

    void init() override;
    void tick() override;
};

struct TextureComponent : Component {

    PositionComponent *cPosition = nullptr;

    TextureComponent(std::string mTex, glm::vec4 mScale = glm::vec4(1, 1, 1, 0), float mAngle = 0);

    GLuint tex = 0;
    glm::vec4 scale;
    float angle;

    void init() override;
    void render() override;
};

struct HealthComponent : Component {

    HealthComponent(float mMaxHealth);

    float maxHealth = 0;
    float health = 0;

    void damage(float damage);
    void heal(float heal);
    void setMaxHealth(float mMaxHealth);
};

struct InventoryComponent : Component {

    InventoryComponent();

    int itemCount = 0;
    int modifierCount = 0;

    bool addItem();
    // void removeItem(int slot);
    void listInventory();
};

struct PlayerComponent : Component {

    PhysicsComponent *cPhysics = nullptr;
    InventoryComponent *cInventory = nullptr;

    float acceleration = 0;

    void init() override;
    void tick() override;
};

#endif

