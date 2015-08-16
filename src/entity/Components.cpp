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
    // TODO: Do this better
    size = mSize/2;
}

void CollisionComponent::init() {

    cPosition = &entity->getComponent<PositionComponent>();
    cHitbox = &entity->getComponent<HitboxComponent>();
}

mat4 CollisionComponent::checkCollision(vec4 mVelocity) {

	// X-axis
	mat4 tempMoveX = translate(IDENTITY, vec3(mVelocity.x, 0, 0));

	vec4 tempPositionX0 = (tempMoveX * cPosition->position) + cHitbox->origin;

	vec4 tempPositionX1 = tempPositionX0;
	tempPositionX1.x += cHitbox->size.x;

	vec4 tempPositionX2 = tempPositionX0;
	tempPositionX2.y += cHitbox->size.y;

	vec4 tempPositionX3 = tempPositionX0;
	tempPositionX3.x += cHitbox->size.x;
	tempPositionX3.y += cHitbox->size.y;

	mat4 moveX = scale(IDENTITY, vec3(1, 1, 1));
	if (Level::isSolid(tempPositionX0) || Level::isSolid(tempPositionX1) || Level::isSolid(tempPositionX2) || Level::isSolid(tempPositionX3)) {

	    moveX = scale(IDENTITY, vec3(0, 1, 1));
	}

	// Y-axis
	mat4 tempMoveY = translate(IDENTITY, vec3(0, mVelocity.y, 0));

	vec4 tempPositionY0 = (tempMoveY * cPosition->position) + cHitbox->origin;

	vec4 tempPositionY1 = tempPositionY0;
	tempPositionY1.x += cHitbox->size.x;

	vec4 tempPositionY2 = tempPositionY0;
	tempPositionY2.y += cHitbox->size.y;

	vec4 tempPositionY3 = tempPositionY0;
	tempPositionY3.x += cHitbox->size.x;
	tempPositionY3.y += cHitbox->size.y;

	mat4 moveY = scale(IDENTITY, vec3(1, 1, 1));
	if (Level::isSolid(tempPositionY0) || Level::isSolid(tempPositionY1) || Level::isSolid(tempPositionY2) || Level::isSolid(tempPositionY3)) {

	    moveY = scale(IDENTITY, vec3(1, 0, 1));
	}

	mVelocity = moveX * moveY * mVelocity;
	mat4 move = translate(IDENTITY, vec3(mVelocity.x, mVelocity.y, mVelocity.z));
	
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
