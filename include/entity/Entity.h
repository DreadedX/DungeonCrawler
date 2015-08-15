#ifndef ENTITY_H
#define ENTITY_H

class Entity;
class Manager;

struct Component {
    Entity* entity;
    
    virtual void init() {}
    virtual void tick() {}
    virtual void render() {}

    virtual ~Component() {}
};

namespace Internal {

    inline std::size_t getUniqueComponentID() noexcept {

	static std::size_t lastID{0u};
	return lastID++;
    }
}

template<typename T> inline std::size_t getComponentTypeID() noexcept {

    static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");

    static std::size_t typeID{Internal::getUniqueComponentID()};

    return typeID;
}

constexpr std::size_t maxComponents{32};
constexpr std::size_t maxGroups{32};

class Entity {

    private:
	Manager& manager;

	bool alive = true;
	std::vector<std::unique_ptr<Component>> components;

	std::array<Component*, maxComponents> componentArray;
	std::bitset<maxComponents> componentBitset;

	std::bitset<maxComponents> groupBitset;


    public:

	Entity(Manager &mManager) : manager(mManager) {}

	void tick();
	void render();

	bool isAlive() const;
	void destroy();

	bool hasGroup(std::size_t mGroup) const noexcept;
	void addGroup(std::size_t mGroup);
	void removeGroup(std::size_t mGroup);

	template<typename T> bool hasComponent() const {

	    return componentBitset[getComponentTypeID<T>()];
	}

	template<typename T, typename... TArgs> T &addComponent(TArgs&&... mArgs) {

	    assert(!hasComponent<T>());

	    T* c(new T(std::forward<TArgs>(mArgs)...));
	    c->entity = this;

	    std::unique_ptr<Component> uPtr{c};
	    components.emplace_back(std::move(uPtr));

	    componentArray[getComponentTypeID<T>()] = c;
	    componentBitset[getComponentTypeID<T>()] = true;

	    c->init();
	    return *c;
	}

	template<typename T> T &getComponent() const {

	    assert(hasComponent<T>());
	    auto ptr = componentArray[getComponentTypeID<T>()];
	    return *reinterpret_cast<T*>(ptr);
	}

};

class Manager {

    private:

	std::vector<std::unique_ptr<Entity>> entities;
	std::array<std::vector<Entity*>, maxGroups> groupedEntities;


    public:

	void tick();
	void render();

	void addToGroup(Entity *mEntity, std::size_t mGroup);

	std::vector<std::unique_ptr<Entity>> &getEntities();

	std::vector<Entity*> &getEntitiesByGroup(std::size_t mGroup);

	void refresh();

	Entity &addEntity();
};


#endif

