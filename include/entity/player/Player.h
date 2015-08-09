#ifndef PLAYER_H
#define PLAYER_H

class Player {

    public:

	Player();
	virtual ~Player();

	vec4 position = vec4(5, 5, 0.0f, 1.0f);

	virtual void init() = 0;
	void tick();
	void render();

	// bool addItem(const ItemTypeData *itemType, const ModifierData *modifier, const EnchanmentData *enchantment);
	bool addItem(Item item);
	void removeItem(int slot);

	bool changeMoney(float change);

	//NOTE: This is for testing
	void listInventory();

    protected:

	void init(std::string texture);
	virtual void attack() = 0;
};

#endif
