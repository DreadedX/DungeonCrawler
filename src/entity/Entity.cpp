# include "Standard.h"

// Entity
void Entity::tick() {

    for (auto& c : components) {

	c->tick();
    }
}
void Entity::render() {

    for (auto& c : components) {

	c->render();
    }
}

bool Entity::isAlive() const {

    return alive;
}

void Entity::destroy() {

    alive = false;
}

bool Entity::hasGroup(std::size_t mGroup) const noexcept {

    return groupBitset[mGroup];
}

void Entity::addGroup(std::size_t mGroup) {

    groupBitset[mGroup] = true;
    manager.addToGroup(this, mGroup);
}

void Entity::removeGroup(std::size_t mGroup) {

    groupBitset[mGroup] = false;
}

// Manager

void Manager::tick() {

    for (auto& e : entities) {

	e->tick();
    }
}

void Manager::render() {

    for (auto& e : entities) {

	e->render();
    }
}

void Manager::addToGroup(Entity *mEntity, std::size_t mGroup) {

    groupedEntities[mGroup].emplace_back(mEntity);
}

std::vector<std::unique_ptr<Entity>> &Manager::getEntities() {

    return entities;
}

std::vector<Entity*> &Manager::getEntitiesByGroup(std::size_t mGroup) {

    return groupedEntities[mGroup];
}

void Manager::refresh() {

    for (std::size_t i = 0; i < maxGroups; i++) {

	auto& v(groupedEntities[i]);

	v.erase(
		std::remove_if(std::begin(v), std::end(v),
		    [i](Entity *mEntity) {

			return !mEntity->isAlive() || !mEntity->hasGroup(i);
		    }),
		    std::end(v));

    }

    entities.erase(
	    std::remove_if(std::begin(entities), std::end(entities),
		[](const std::unique_ptr<Entity> &mEntity) {

		    return !mEntity->isAlive();
		}),
		std::end(entities));
}

Entity &Manager::addEntity() {
    
    Entity *e(new Entity(*this));
    std::unique_ptr<Entity> uPtr{e};
    entities.emplace_back(std::move(uPtr));
    return *e;
}
