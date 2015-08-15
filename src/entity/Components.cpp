# include "Standard.h"

PositionComponent::PositionComponent(vec4 mPosition) {

    position = mPosition;
}

void PhysicsComponent::init() {

    cPosition = &entity->getComponent<PositionComponent>();

    if (entity->hasComponent<CollisionComponent>()) {
	hasCollision = true;
	cCollision = &entity->getComponent<CollisionComponent>();
    }
}

HitboxComponent::HitboxComponent(vec4 mOrigin, vec4 mSize) {

    origin = mOrigin;
    size = mSize;
}

void CollisionComponent::init() {

    cPosition = &entity->getComponent<PositionComponent>();
    cHitbox = &entity->getComponent<HitboxComponent>();
}

mat4 CollisionComponent::checkCollision(vec4 mVelocity) {

	mat4 move = translate(IDENTITY, vec3(mVelocity.x, mVelocity.y, mVelocity.z));

	vec4 tempPosition = move * cPosition->position;

	if (Level::isSolid(tempPosition)) {

	    move = translate(IDENTITY, vec3(-mVelocity.x, -mVelocity.y, -mVelocity.z));
	}

	return move;
}

void PhysicsComponent::tick() {

    mat4 move;

    if (hasCollision) {

	move = cCollision->checkCollision(velocity);
    } else {

	move = translate(IDENTITY, vec3(velocity.x, velocity.y, velocity.z));
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
}

TextureComponent::TextureComponent(std::string mTex, vec4 mScale) {

    tex = Texture::load(mTex);
    scale = mScale;
}

// bool InventoryComponent::addItem(Item item) {
//
//     for (int i = 0; i < INVENTORY_SIZE; i++) {
//
// 	if (inventory[i]->getName() == "Empty") {
//
// 	    *inventory[i] = item;
// 	    return true;
// 	}
//     }
//
//     return false;
// }
//
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
