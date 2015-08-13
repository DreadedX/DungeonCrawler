#ifndef PLAYER_H
#define PLAYER_H

class Player: public Entity {

    public:

	Player(vec4 position);
	virtual ~Player();

	void tick();
	void render();

	bool addItem(Item item);
	void removeItem(int slot);

	bool changeMoney(float change);

	//NOTE: This is for testing
	void listInventory();

	virtual void attack() = 0;

    protected:

	void init(std::string texture, vec4 scale);
	GLuint tex = 0;

    private:

	vec4 scale = vec4(1, 1, 1, 0);
};

#endif
