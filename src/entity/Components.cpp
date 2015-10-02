# include "Standard.h"
PositionComponent::PositionComponent(glm::vec4 mPosition) {

    position = mPosition;
}

void PhysicsComponent::init() {

    cPosition = &entity->getComponent<PositionComponent>();

    if (entity->hasComponent<CollisionComponent>()) {
	hasCollision = true;
	cCollision = &entity->getComponent<CollisionComponent>();
    }
}

HitboxComponent::HitboxComponent(glm::vec4 mOrigin, glm::vec4 mSize) {

    origin = mOrigin;
    // TODO: Do this better
    size = mSize/2;
}

void CollisionComponent::init() {

    cPosition = &entity->getComponent<PositionComponent>();
    cHitbox = &entity->getComponent<HitboxComponent>();
}

glm::mat4 CollisionComponent::checkCollision(glm::vec4 mVelocity) {

    // X-axis
    glm::mat4 tempMoveX = glm::translate(IDENTITY, glm::vec3(mVelocity.x, 0, 0));

    glm::vec4 tempPositionX0 = (tempMoveX * cPosition->position) + cHitbox->origin;

    glm::vec4 tempPositionX1 = tempPositionX0;
    tempPositionX1.x += cHitbox->size.x;

    glm::vec4 tempPositionX2 = tempPositionX0;
    tempPositionX2.y += cHitbox->size.y;

    glm::vec4 tempPositionX3 = tempPositionX0;
    tempPositionX3.x += cHitbox->size.x;
    tempPositionX3.y += cHitbox->size.y;

    glm::mat4 moveX = glm::scale(IDENTITY, glm::vec3(1, 1, 1));
    if (Level::isSolid(tempPositionX0) || Level::isSolid(tempPositionX1) || Level::isSolid(tempPositionX2) || Level::isSolid(tempPositionX3)) {

	moveX = glm::scale(IDENTITY, glm::vec3(0, 1, 1));
    }

    // Y-axis
    glm::mat4 tempMoveY = glm::translate(IDENTITY, glm::vec3(0, mVelocity.y, 0));

    glm::vec4 tempPositionY0 = (tempMoveY * cPosition->position) + cHitbox->origin;

    glm::vec4 tempPositionY1 = tempPositionY0;
    tempPositionY1.x += cHitbox->size.x;

    glm::vec4 tempPositionY2 = tempPositionY0;
    tempPositionY2.y += cHitbox->size.y;

    glm::vec4 tempPositionY3 = tempPositionY0;
    tempPositionY3.x += cHitbox->size.x;
    tempPositionY3.y += cHitbox->size.y;

    glm::mat4 moveY = glm::scale(IDENTITY, glm::vec3(1, 1, 1));
    if (Level::isSolid(tempPositionY0) || Level::isSolid(tempPositionY1) || Level::isSolid(tempPositionY2) || Level::isSolid(tempPositionY3)) {

	moveY = glm::scale(IDENTITY, glm::vec3(1, 0, 1));
    }

    mVelocity = moveX * moveY * mVelocity;
    glm::mat4 move = glm::translate(IDENTITY, glm::vec3(mVelocity.x, mVelocity.y, mVelocity.z));

    return move;
}

bool CollisionComponent::hasCollided(glm::vec4 mVelocity) {

    // X-axis
    glm::mat4 tempMoveX = glm::translate(IDENTITY, glm::vec3(mVelocity.x, 0, 0));

    glm::vec4 tempPositionX0 = (tempMoveX * cPosition->position) + cHitbox->origin;

    glm::vec4 tempPositionX1 = tempPositionX0;
    tempPositionX1.x += cHitbox->size.x;

    glm::vec4 tempPositionX2 = tempPositionX0;
    tempPositionX2.y += cHitbox->size.y;

    glm::vec4 tempPositionX3 = tempPositionX0;
    tempPositionX3.x += cHitbox->size.x;
    tempPositionX3.y += cHitbox->size.y;

    if (Level::isSolid(tempPositionX0) || Level::isSolid(tempPositionX1) || Level::isSolid(tempPositionX2) || Level::isSolid(tempPositionX3)) {

	return true;
    }

    // Y-axis
    glm::mat4 tempMoveY = glm::translate(IDENTITY, glm::vec3(0, mVelocity.y, 0));

    glm::vec4 tempPositionY0 = (tempMoveY * cPosition->position) + cHitbox->origin;

    glm::vec4 tempPositionY1 = tempPositionY0;
    tempPositionY1.x += cHitbox->size.x;

    glm::vec4 tempPositionY2 = tempPositionY0;
    tempPositionY2.y += cHitbox->size.y;

    glm::vec4 tempPositionY3 = tempPositionY0;
    tempPositionY3.x += cHitbox->size.x;
    tempPositionY3.y += cHitbox->size.y;

    if (Level::isSolid(tempPositionY0) || Level::isSolid(tempPositionY1) || Level::isSolid(tempPositionY2) || Level::isSolid(tempPositionY3)) {

	return true;
    }

    return false;
}

void PhysicsComponent::tick() {

    glm::mat4 move;

    if (hasCollision) {

	move = cCollision->checkCollision(velocity);
    } else {

	move = translate(IDENTITY, glm::vec3(velocity.x, velocity.y, velocity.z));
    }

    cPosition->position = move * cPosition->position;

    if ((velocity.x > -0.01f) && (velocity.x < 0.01f) && velocity.x != 0) {

	velocity.x = 0;
    }

    if ((velocity.y > -0.01f) && (velocity.y < 0.01f) && velocity.y != 0) {

	velocity.y = 0;
    }

    velocity = friction * velocity;
}

ProjectileComponent::ProjectileComponent(glm::vec4 mVelocity) {

    velocity = mVelocity;
}

void ProjectileComponent::init() {

    cPosition = &entity->getComponent<PositionComponent>();
    cCollision = &entity->getComponent<CollisionComponent>();
    cPhysics = &entity->getComponent<PhysicsComponent>();
    cPhysics->velocity = velocity;
}

void ProjectileComponent::tick() {

    life--;
    if (life <= 0) {

	entity->destroy();
    }
    
    // TODO: Make this look graphicly nicer
    if (cCollision->hasCollided(velocity)) {

	velocity = glm::vec4(0, 0, 0, 0);
    }

    cPhysics->velocity = velocity;
}

void PlayerComponent::init() {

    cPhysics = &entity->getComponent<PhysicsComponent>();
    cInventory = &entity->getComponent<InventoryComponent>();

    acceleration = cPhysics->getAccelaration(1.5f/16);
}

void PlayerComponent::tick() {

    if (Input::isPressed(Key::UP)) {

	cPhysics->velocity.y += acceleration;
    }

    if (Input::isPressed(Key::DOWN)) {

	cPhysics->velocity.y -= acceleration;
    }

    if (Input::isPressed(Key::LEFT)) {

	cPhysics->velocity.x -= acceleration;
    }

    if (Input::isPressed(Key::RIGHT)) {

	cPhysics->velocity.x += acceleration;
    }

    if (Input::isPressed(GLFW_MOUSE_BUTTON_LEFT)) {

	if (Level::getManager()->getEntitiesByGroup(GROUP_INVENTORY).size() > 0) {

	    Level::getManager()->getEntitiesByGroup(GROUP_INVENTORY)[0]->getComponent<ItemComponent>().attack();
	}
    }

    // TODO: Make this only use items that are equiped
    for (auto &item : Level::getManager()->getEntitiesByGroup(GROUP_INVENTORY)) {

	item->getComponent<ItemComponent>().passive();
    }

#if DEBUG_MODE
    if (Input::isPressed(Key::DEBUG_NOCLIP)) {

	Input::setState(Key::DEBUG_NOCLIP, false);

	cPhysics->hasCollision = !cPhysics->hasCollision;
	Log::print(String::format("No clip: %i", cPhysics->hasCollision), DEBUG);
    }

    if (Input::isPressed(Key::DEBUG_BOOST)) {

	Input::setState(Key::DEBUG_BOOST, false);

	static bool boost = false;
	if (boost) {

	    acceleration /= 10;
	    boost = false;
	} else {

	    acceleration *= 10;
	    boost = true;
	}

	Log::print(String::format("Boost: %i", boost), DEBUG);
    }
#endif
}

HealthComponent::HealthComponent(float mMaxHealth) {

    maxHealth = mMaxHealth;
    health = mMaxHealth;
}

void HealthComponent::damage(float damage) {

    health -= damage;

    Log::print(String::format("Took %f damage", damage), DEBUG);

    if (health <= 0) {

	// TODO: Add better death handeling
	entity->destroy();
    }
}

void HealthComponent::heal(float heal) {

    if (health != maxHealth) {

	health += heal;

	Log::print(String::format("Healed for %f", heal), DEBUG);
    }

    if (health >= maxHealth) {

	health = maxHealth;
    }
}

void HealthComponent::setMaxHealth(float mMaxHealth) {

    maxHealth = mMaxHealth;
    health = mMaxHealth;
}

InventoryComponent::InventoryComponent() {

    static int itemsID = Reader::getId("config/items");
    static byte json[1000] = {0x00};
    static rapidjson::Document d;

    if (json[0] == 0x00) {
	Reader::read(itemsID, json);
    
	d.Parse(reinterpret_cast<char const*>(json));

	itemCount = d["items"].Size();
	modifierCount = d["modifiers"].Size();
    }
}

bool InventoryComponent::addItem() {

    static long seedItem = time(NULL);

    Entity &item = Level::getManager()->addEntity();
    item.addGroup(GROUP_INVENTORY);
    item.addComponent<ItemComponent>(Randomizer::random(itemCount, &seedItem) - 1);
    // item.addComponent<ItemComponent>(Randomizer::random(itemCount, &seedItem) - 1);
    item.addComponent<ModifierItemComponent>(Randomizer::random(modifierCount, &seedItem) - 1);

    // Gui::printLine(String::format("Picked up: %s", item.getComponent<ItemComponent>().name.c_str()));
    TextBox::add(String::format("Picked up: %s", item.getComponent<ItemComponent>().name.c_str()));

    // TODO: Add inventory size checking
    return true;
}

// void InventoryComponent::removeItem(int slot) {
//
//     delete inventory[slot];
//     inventory[slot] = nullptr;
//     inventory[slot] = new Item;
// }

void InventoryComponent::listInventory() {

    Log::print("----Inventory----", DEBUG);

    for (auto& entity : Level::getManager()->getEntitiesByGroup(GROUP_INVENTORY)) {

	ItemComponent item = entity->getComponent<ItemComponent>();

	Log::print(String::format("%s %.1f %.1f", item.name.c_str(), item.value, item.weight), DEBUG);
    }
}

TextureComponent::TextureComponent(std::string mTex, glm::vec4 mScale, float mAngle) {

    tex = Texture::load(mTex);
    scale = mScale;
    angle = mAngle;
}

void TextureComponent::init() {

    cPosition = &entity->getComponent<PositionComponent>();
}

void TextureComponent::render() {

    Render::entity(cPosition->position, scale/2, angle, tex);
}
