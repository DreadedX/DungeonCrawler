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

void PlayerComponent::init() {

    cPhysics = &entity->getComponent<PhysicsComponent>();
    // cClass = &entity->getComponent<ClassComponent>();

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

#if DEBUG_MODE
    if (Input::isPressed(GLFW_KEY_SPACE)) {

	Input::setState(GLFW_KEY_SPACE, false);

	cPhysics->hasCollision = !cPhysics->hasCollision;
	Log::print(String::format("No clip: %i", cPhysics->hasCollision), DEBUG);
    }

    if (Input::isPressed(GLFW_KEY_LEFT_SHIFT)) {

	Input::setState(GLFW_KEY_LEFT_SHIFT, false);

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

TextureComponent::TextureComponent(std::string mTex, glm::vec4 mScale) {

    tex = Texture::load(mTex);
    scale = mScale;
}

InventoryComponent::InventoryComponent() {

    static int itemsID = IO::Reader::getId("config/items");
    static byte json[1000] = {0x00};
    static rapidjson::Document d;

    if (json[0] == 0x00) {
	IO::Reader::read(itemsID, json);
    
	d.Parse(reinterpret_cast<char const*>(json));

	itemCount = d["items"].Size();
	modifierCount = d["modifiers"].Size();
    }
}

bool InventoryComponent::addItem() {

    static long seedItem = time(NULL);

    Entity &item = inventory.addEntity();
    item.addComponent<ItemComponent>(Randomizer::random(itemCount, &seedItem) - 1);
    item.addComponent<ModifierItemComponent>(Randomizer::random(modifierCount, &seedItem) - 1);

    // TODO: Add inventory size checking
    return true;
}

// void InventoryComponent::removeItem(int slot) {
//
//     delete inventory[slot];
//     inventory[slot] = nullptr;
//     inventory[slot] = new Item;
// }
//
void InventoryComponent::listInventory() {

    Log::print("----Inventory----", DEBUG);

    for (auto& entity : inventory.getEntities()) {

	ItemComponent item = entity->getComponent<ItemComponent>();

	Log::print(String::format("%s %.1f %.1f", item.name.c_str(), item.value, item.weight), DEBUG);
    }
}

void TextureComponent::init() {

    cPosition = &entity->getComponent<PositionComponent>();
}


void TextureComponent::render() {

    Render::entity(cPosition->position, scale/2, tex);
}
